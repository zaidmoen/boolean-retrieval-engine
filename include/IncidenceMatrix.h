#pragma once

#include "InvertedIndex.h"

#include <string>
#include <vector>

class IncidenceMatrix {
public:
    void build(const InvertedIndex& index, int documentCount);
    void print() const;

private:
    std::vector<std::string> rowTerms;
    std::vector<std::vector<int>> values;
};

