#pragma once

#include <string>
#include <vector>

class TextProcessor {
public:
    std::vector<std::string> tokenize(const std::string& text) const;
};

