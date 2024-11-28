# Hierarchical-Text-Classifier
## Overview
This project implements a hierarchical text classification system using a trie data structure to represent multi-level classifications. The system integrates a Large Language Model (LLM) via socket programming to dynamically classify text inputs and refine classifications based on a hierarchical structure.

Key functionalities include inserting classifications, classifying text inputs, erasing classifications, and traversing the trie for hierarchical relationships.

## Features
* Efficient Hierarchical Classification: Implements a trie data structure to represent and traverse hierarchical classes.
* Dynamic Classification with LLM: Utilizes socket programming to interact with an LLM for text classification at each hierarchy level.
* Command-Based Operations: Supports commands like LOAD, INSERT, CLASSIFY, ERASE, PRINT, and CLEAR.
* Robust Error Handling: Ensures valid input parsing and handles exceptions for unsupported formats.
* Technologies Used
* C++: Core implementation language.
* Socket Programming: Enables communication with the LLM for dynamic classification.
* Trie Data Structure: Represents hierarchical classifications efficiently.
* Linux Environment: Developed and tested on a Linux system for compatibility and performance

## Dependencies
* C++ Compiler: GCC or Clang.
* Linux OS: For socket programming compatibility.
* LLM Socket Library: Provided in the project starter files (ece250_socket.cpp).
* How It Works
* The trie data structure organizes classes hierarchically, enabling efficient lookup and management of classifications.
* For text classification, the program interacts with an LLM to assign classes dynamically.
* Commands are parsed and executed to perform operations on the trie or communicate with the LLM.
