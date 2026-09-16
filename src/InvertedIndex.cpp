#include "InvertedIndex.h"

void InvertedIndex::addDocument(int documentId,
                                const std::vector<std::string>& terms) {
    // The map keeps terms sorted, which makes the output easier to read.
    for (const auto& term : terms) {
        index[term][documentId]++;
    }
}

const PostingList* InvertedIndex::find(const std::string& term) const {
    const auto iterator = index.find(term);
    return iterator == index.end() ? nullptr : &iterator->second;
}

const std::map<std::string, PostingList>& InvertedIndex::entries() const {
    return index;
}

std::vector<std::string> InvertedIndex::terms() const {
    std::vector<std::string> result;
    for (const auto& [term, postings] : index) {
        (void)postings;
        result.push_back(term);
    }
    return result;
}

