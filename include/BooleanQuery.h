#pragma once

#include "InvertedIndex.h"

#include <set>
#include <string>

class BooleanQuery {
public:
    BooleanQuery(const InvertedIndex& index, int documentCount);
    std::set<int> evaluate(const std::string& query) const;

private:
    std::set<int> documentsForTerm(const std::string& term) const;
    std::set<int> allDocuments() const;
    static std::vector<std::string> split(const std::string& query);

    const InvertedIndex& index;
    int documentCount;
};

