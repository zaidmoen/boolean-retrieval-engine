#pragma once

#include <map>
#include <string>
#include <vector>

#include "LinkedList.h"

using namespace std;

class InvertedIndex {
public:
    void addDocument(int documentId, const vector<string>& terms);

    const PostingList* find(const string& term) const;
    const map<string, PostingList>& entries() const;
    vector<string> terms() const;

private:
    map<string, PostingList> index;
};
