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

    size_t documentFrequency(const string& term) const {
        const PostingList* postings = find(term);
        return postings == nullptr ? 0 : postings->size();
    }

private:
    map<string, PostingList> index;
};
