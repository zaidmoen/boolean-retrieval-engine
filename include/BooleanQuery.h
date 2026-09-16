#pragma once

#include "InvertedIndex.h"

#include <set>
#include <string>

using namespace std;

class BooleanQuery {
public:
    BooleanQuery(const InvertedIndex& index, int documentCount);
    set<int> evaluate(const string& query) const;

private:
    set<int> documentsForTerm(const string& term) const;
    set<int> allDocuments() const;
    static vector<string> split(const string& query);

    const InvertedIndex& index;
    int documentCount;
};
