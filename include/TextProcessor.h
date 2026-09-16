#pragma once

#include <string>
#include <vector>

using namespace std;

class TextProcessor {
public:
    vector<string> tokenize(const string& text) const;
};
