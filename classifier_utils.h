#ifndef CLASSIFIER_UTILS_H
#define CLASSIFIER_UTILS_H

#include "ece250_socket.h"
#include <string>
#include <vector>

// takes a text input and a vector of labels, combines the labels
// into a single comma-separated string, and uses the label function
std::string classify_text(const std::string &text, const std::vector<std::string> &labels) {
    std::string label_str;
    for (size_t i = 0; i < labels.size(); ++i) {
        label_str += labels[i];
        if (i < labels.size() - 1) label_str += ",";
    }
    return labelText(text, label_str);
}

#endif // CLASSIFIER_UTILS_H
