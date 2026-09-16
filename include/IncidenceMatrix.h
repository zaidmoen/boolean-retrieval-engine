#pragma once

#include "InvertedIndex.h"

#include <string>
#include <vector>

using namespace std;

class IncidenceMatrix {
public:
    void build(const InvertedIndex& index, int documentCount);
    void print() const;

private:
    vector<string> rowTerms;
    vector<vector<int>> values;
};
