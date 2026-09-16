#include "TextProcessor.h"

#include <cctype>

using namespace std;

vector<string> TextProcessor::tokenize(const string& text) const {
    vector<string> tokens;
    string current;

    for (unsigned char character : text) {
        if (isalnum(character)) {
            current += static_cast<char>(tolower(character));
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
