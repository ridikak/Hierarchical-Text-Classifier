#include "ece250_socket.h"
#include "Trie.h"
#include "IllegalArgumentException.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Function to split a string by commas and return a vector of strings
// This is used to parse input arguments for commands like INSERT and ERASE
std::vector<std::string> splitStringToVector(const std::string& str) {
    std::vector<std::string> result;
    std::istringstream stream(str); // Create a string stream from the input string
    std::string part;

    // Extract substrings separated by commas
    while (std::getline(stream, part, ',')) {
        result.push_back(part);
    }

    return result; // Return the vector of substrings
}

int main() {
    Trie trie; // Create an instance of the Trie data structure
    std::string command, argument; // Variables to hold command and argument inputs

    // Main loop to process commands from standard input
    while (std::cin >> command) {
        if (command == "LOAD") { // Command to load classifications from a file
            std::cin >> argument; // Read the filename
            trie.load(argument); // Load classifications into the Trie
        } else if (command == "INSERT") { // Command to insert a classification
            std::cin >> argument; // Read the classification as a comma-separated string
            try {
                std::vector<std::string> classification = splitStringToVector(argument);
                // Insert the classification into the Trie and output success or failure
                if (trie.insert(classification)) {
                    std::cout << "success\n";
                } else {
                    std::cout << "failure\n";
                }
            } catch (const IllegalArgumentException&) {
                std::cout << "illegal argument\n"; // Handle invalid input
            }
        } else if (command == "CLASSIFY") { // Command to classify input text
            std::cin >> argument; // Read the input text
            try {
                // Perform classification and output the result
                std::cout << trie.classify(argument) << "\n";
            } catch (const IllegalArgumentException&) {
                std::cout << "illegal argument\n"; // Handle invalid input
            }
        } else if (command == "ERASE") { // Command to erase a classification
            std::cin >> argument; // Read the classification as a comma-separated string
            try {
                std::vector<std::string> classification = splitStringToVector(argument);
                // Erase the classification and output success or failure
                if (trie.erase(classification)) {
                    std::cout << "success\n";
                } else {
                    std::cout << "failure\n";
                }
            } catch (const IllegalArgumentException&) {
                std::cout << "illegal argument\n"; // Handle invalid input
            }
        } else if (command == "PRINT") { // Command to print all classifications in the Trie
            trie.print();
        } else if (command == "EMPTY") { // Command to check if the Trie is empty
            // Output whether the Trie is empty (1) or not (0)
            std::cout << (trie.empty() ? "empty 1\n" : "empty 0\n");
        } else if (command == "CLEAR") { // Command to clear all classifications from the Trie
            trie.clear(); // Clear the Trie
            std::cout << "success\n";
        } else if (command == "SIZE") { // Command to get the number of classifications
            // Output the number of classifications in the Trie
            std::cout << "number of classifications is " << trie.size() << "\n";
        } else if (command == "EXIT") { // Command to exit the program
            break; // Exit the loop without printing any additional output
        }
    }

    return 0; // Return 0 to indicate successful execution
}


