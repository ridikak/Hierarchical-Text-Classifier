#ifndef ILLEGAL_ARGUMENT_EXCEPTION_H
#define ILLEGAL_ARGUMENT_EXCEPTION_H

#include <exception> // Provides the base exception class

// Custom exception class for handling illegal arguments
class IllegalArgumentException : public std::exception {
public:
    // Override the what() method to provide a custom error message
    const char* what() const noexcept override {
        return "illegal argument"; // The error message returned for this exception
    }
};

#endif // ILLEGAL_ARGUMENT_EXCEPTION_H

