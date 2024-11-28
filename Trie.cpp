#include "Trie.h"
#include "classifier_utils.h"
#include <iostream>
#include <algorithm> // For std::find

// Constructor for TrieNode
// Initializes the node with a given label and terminal status
TrieNode::TrieNode(const std::string &label, bool is_terminal)
    : label(label), is_terminal(is_terminal), children() {}

// Destructor for TrieNode
// Recursively deletes all child nodes to prevent memory leaks
TrieNode::~TrieNode() {
    for (TrieNode *child : children) {
        delete child;
    }
}

// Constructor for Trie
// Initializes the Trie with an empty root node and zero classifications
Trie::Trie() : root(new TrieNode("")), classification_count(0) {}

// Destructor for Trie
// Clears the Trie and deletes the root node
Trie::~Trie() {
    clear();
    delete root;
}

// Loads classifications from a file into the Trie
void Trie::load(const std::string &filename) {
    std::FILE* file = std::fopen(filename.c_str(), "r");
    if (!file) {
        return; // File couldn't be opened
    }

    char buffer[1024]; // Temporary buffer for reading lines
    while (std::fgets(buffer, sizeof(buffer), file)) {
        // Parse the line into classification labels
        std::vector<std::string> classification;
        std::string label;
        for (size_t i = 0; buffer[i] != '\0' && buffer[i] != '\n'; ++i) {
            if (buffer[i] == ',') {
                classification.push_back(label);
                label.clear();
            } else {
                label += buffer[i];
            }
        }
        if (!label.empty()) {
            classification.push_back(label);
        }

        // Insert the parsed classification into the Trie
        insert(classification);
    }

    std::fclose(file);
    std::cout << "success" << std::endl;
}

// Finds the node corresponding to a given classification path
TrieNode* Trie::find_node(const std::vector<std::string> &classification) {
    TrieNode *current = root;
    for (const auto &label : classification) {
        bool found = false;
        for (TrieNode *child : current->children) {
            if (child && child->label == label) {
                current = child;
                found = true;
                break;
            }
        }
        if (!found) return nullptr; // Path does not exist
    }
    return current;
}

// Inserts a classification path into the Trie
bool Trie::insert(const std::vector<std::string> &classification) {
    TrieNode *current = root;

    for (const auto &label : classification) {
        // Validate label
        for (char ch : label) {
            if (isupper(ch)) {
                throw IllegalArgumentException();
            }
        }

        // Check if the current node is already terminal
        // If it is terminal but we are inserting deeper, we need to "unmark" it.
        if (current->is_terminal) {
            current->is_terminal = false;
        }

        // Check if the label exists among children
        TrieNode *child = nullptr;
        for (TrieNode *&existing_child : current->children) {
            if (existing_child && existing_child->label == label) {
                child = existing_child;
                break;
            }
        }

        // Create a new node if label does not exist
        if (!child) {
            child = new TrieNode(label);
            current->children.push_back(child);
        }

        // Move to the child node
        current = child;
    }

    // At the end, check if the current node is already terminal
    if (current->is_terminal) {
        return false;
    }

    // Mark the node as terminal and increment count
    current->is_terminal = true;
    classification_count++;
    return true;
}

// Classifies an input text using the Trie and the external classifier utility
std::string Trie::classify(const std::string &input) {
    std::vector<std::string> path;
    TrieNode *current = root;

    while (true) {
        std::vector<std::string> labels;
        for (TrieNode *child : current->children) {
            if (child && child->is_terminal) {
                labels.push_back(child->label);
            }
        }
        if (labels.empty()) break;

        // Use the classifier utility to classify the input text
        std::string result = classify_text(input, labels);

        bool found = false;
        for (TrieNode *child : current->children) {
            if (child && child->label == result && child->is_terminal) {
                path.push_back(result);
                current = child;
                found = true;
                break;
            }
        }
        if (!found) break;
    }

    // Convert the classification path to a comma-separated string
    std::string output;
    for (size_t i = 0; i < path.size(); ++i) {
        output += path[i];
        if (i < path.size() - 1) output += ",";
    }
    return output;
}

// Removes a classification path from the Trie
bool Trie::erase(const std::vector<std::string> &classification) {
    TrieNode *current = root;
    std::vector<std::pair<TrieNode *, TrieNode *>> path; // Stores the path (child, parent)

    for (const std::string &label : classification) {
        TrieNode *parent = current;
        auto it = std::find_if(current->children.begin(), current->children.end(),
                               [&label](TrieNode *child) { return child && child->label == label; });

        if (it == current->children.end()) {
            return false; // Classification not found
        }

        current = *it;
        path.emplace_back(current, parent);
    }

    if (!current->is_terminal) {
        return false; // Classification is not terminal
    }

    current->is_terminal = false;

    // Clean up unused nodes
    for (auto it = path.rbegin(); it != path.rend(); ++it) {
        TrieNode *node = it->first;
        TrieNode *parent = it->second;

        if (node->is_terminal || !node->children.empty()) {
            break;
        }

        auto child_it = std::find(parent->children.begin(), parent->children.end(), node);
        if (child_it != parent->children.end()) {
            parent->children.erase(child_it);
        }

        delete node;
    }

    return true;
}

// Helper function to recursively print the Trie
void Trie::print_recursive(TrieNode *node, const std::string &path, std::string &output) const {
    if (!node) return;

    std::string current_path = path.empty() ? node->label : path + "," + node->label;

    if (node->is_terminal) {
        output += current_path + "_";
    }

    for (TrieNode *child : node->children) {
        if (child) {
            print_recursive(child, current_path, output);
        }
    }
}

// Prints all classifications in the Trie
void Trie::print() const {
    if (!root || root->children.empty()) {
        std::cout << std::endl;
        return;
    }

    std::string output;
    for (TrieNode *child : root->children) {
        if (child) {
            print_recursive(child, "", output);
        }
    }

    std::cout << output << std::endl;
}

// Checks if the Trie is empty
bool Trie::empty() const {
    return classification_count == 0;
}

// Clears all classifications from the Trie
void Trie::clear() {
    delete root;
    root = new TrieNode("");
    classification_count = 0;
}

// Returns the number of classifications in the Trie
int Trie::size() const {
    return classification_count;
}



