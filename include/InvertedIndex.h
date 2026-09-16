#pragma once

#include <map>
#include <string>
#include <vector>

using PostingList = std::map<int, int>;

class InvertedIndex {
public:
    void addDocument(int documentId, const std::vector<std::string>& terms);

    const PostingList* find(const std::string& term) const;
    const std::map<std::string, PostingList>& entries() const;
    std::vector<std::string> terms() const;

private:
    std::map<std::string, PostingList> index;
};

