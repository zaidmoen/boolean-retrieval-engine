#include "BooleanQuery.h"

#include <algorithm>
#include <cctype>
#include <sstream>
#include <vector>

using namespace std;

BooleanQuery::BooleanQuery(const InvertedIndex& index, int documentCount)
    : index(index), documentCount(documentCount) {}

vector<string> BooleanQuery::split(const string& query) {
    istringstream stream(query);
    vector<string> tokens;
    string token;

    while (stream >> token) {
        for (char& character : token) {
            character = static_cast<char>(toupper(static_cast<unsigned char>(character)));
        }
        tokens.push_back(token);
    }
    return tokens;
}

set<int> BooleanQuery::allDocuments() const {
    set<int> result;
    for (int id = 1; id <= documentCount; ++id) {
        result.insert(id);
    }
    return result;
}

set<int> BooleanQuery::documentsForTerm(const string& term) const {
    string normalized = term;
    transform(normalized.begin(), normalized.end(), normalized.begin(),
                   [](unsigned char character) {
                       return static_cast<char>(tolower(character));
                   });

    set<int> result;
    const PostingList* postings = index.find(normalized);
    if (postings == nullptr) {
        return result;
    }

    for (const PostingList::Node* current = postings->head(); current != nullptr;
         current = current->next) {
        result.insert(current->value.documentId);
    }
    return result;
}

set<int> BooleanQuery::evaluate(const string& query) const {
    const auto tokens = split(query);
    if (tokens.empty()) {
        return {};
    }

    size_t position = 0;
    auto readOperand = [&]() {
        bool negated = false;
        if (position < tokens.size() && tokens[position] == "NOT") {
            negated = true;
            ++position;
        }

        if (position >= tokens.size()) {
            return set<int>{};
        }

        set<int> operand = documentsForTerm(tokens[position++]);
        if (negated) {
            set<int> complement = allDocuments();
            for (int id : operand) {
                complement.erase(id);
            }
            return complement;
        }
        return operand;
    };

    set<int> result = readOperand();
    while (position < tokens.size()) {
        const string operation = tokens[position++];
        if (operation != "AND" && operation != "OR") {
            continue;
        }

        const set<int> current = readOperand();
        if (operation == "AND") {
            set<int> intersection;
            set_intersection(result.begin(), result.end(), current.begin(),
                                  current.end(),
                                  inserter(intersection, intersection.begin()));
            result = intersection;
        } else {
            result.insert(current.begin(), current.end());
        }
    }

    return result;
}
