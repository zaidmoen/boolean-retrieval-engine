#include "InvertedIndex.h"

using namespace std;

void InvertedIndex::addDocument(int documentId,
                                const vector<string>& terms) {
    // The map keeps terms sorted, and the list keeps document IDs in order.
    for (const auto& term : terms) {
        index[term].add(documentId);
    }
}

const PostingList* InvertedIndex::find(const string& term) const {
    const auto iterator = index.find(term);
    return iterator == index.end() ? nullptr : &iterator->second;
}

const map<string, PostingList>& InvertedIndex::entries() const {
    return index;
}

vector<string> InvertedIndex::terms() const {
    vector<string> result;
    for (const auto& entry : index) {
        const string& term = entry.first;
        result.push_back(term);
    }
    return result;
}
