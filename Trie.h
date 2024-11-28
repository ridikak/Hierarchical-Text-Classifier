#ifndef TRIE_H
#define TRIE_H

#include "IllegalArgumentException.h"
#include <string>
#include <vector>

class TrieNode {
public:
    std::string label;
    bool is_terminal;
    std::vector<TrieNode*> children;  // Replace std::map with vector
// constructor and destructor for trienode
    TrieNode(const std::string &label, bool is_terminal = false);
    ~TrieNode();
};


class Trie {
private:
    // Root node of the Trie
    TrieNode *root;
    // Total number of terminal nodes (classifications)
    int classification_count;
    TrieNode* find_node(const std::vector<std::string> &classification);
    void print_recursive(TrieNode *node, const std::string &path, std::string &output) const;

public:
    Trie();
    ~Trie();
    void load(const std::string &filename);
    bool insert(const std::vector<std::string> &classification);
    std::string classify(const std::string &input);
    bool erase(const std::vector<std::string> &classification);
    void print() const;
    bool empty() const;
    void clear();
    int size() const;
};

#endif // TRIE_H
