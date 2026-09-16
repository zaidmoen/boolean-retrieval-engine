#include "TextProcessor.h"

#include <cctype>

std::vector<std::string> TextProcessor::tokenize(const std::string& text) const {
    std::vector<std::string> tokens;
    std::string current;

    for (unsigned char character : text) {
        if (std::isalnum(character)) {
            current += static_cast<char>(std::tolower(character));
        } else if (!current.empty()) {
            tokens.push_back(current);
            current.clear();
        }
    }

    if (!current.empty()) {
        tokens.push_back(current);
    }

    return tokens;
}

