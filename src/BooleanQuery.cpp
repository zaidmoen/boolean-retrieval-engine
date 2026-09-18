#include "BooleanQuery.h"

#include <algorithm>
#include <cctype>
#include <functional>
#include <stdexcept>
#include <vector>

using namespace std;

BooleanQuery::BooleanQuery(const InvertedIndex& index, int documentCount)
    : index(index), documentCount(documentCount) {}

vector<string> BooleanQuery::split(const string& query) {
    vector<string> tokens;
    string token;

    auto saveToken = [&]() {
        if (token.empty()) {
            return;
        }
        for (char& character : token) {
            character = static_cast<char>(toupper(static_cast<unsigned char>(character)));
        }
        tokens.push_back(token);
        token.clear();
    };

    for (char character : query) {
        if (isspace(static_cast<unsigned char>(character))) {
            saveToken();
        } else if (character == '(' || character == ')') {
            saveToken();
            tokens.push_back(string(1, character));
        } else {
            token += character;
        }
    }
    saveToken();

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
    const vector<string> tokens = split(query);
    if (tokens.empty()) {
        return {};
    }

    size_t position = 0;
    function<set<int>()> readOr;
    function<set<int>()> readAnd;
    function<set<int>()> readNot;
    function<set<int>()> readPrimary;

    readPrimary = [&]() {
        if (position >= tokens.size()) {
            throw invalid_argument("Missing term at the end of the query.");
        }

        if (tokens[position] == "(") {
            ++position;
            set<int> result = readOr();
            if (position >= tokens.size() || tokens[position] != ")") {
                throw invalid_argument("Missing closing parenthesis.");
            }
            ++position;
            return result;
        }

        if (tokens[position] == ")" || tokens[position] == "AND" ||
            tokens[position] == "OR") {
            throw invalid_argument("Expected a search term.");
        }

        return documentsForTerm(tokens[position++]);
    };

    readNot = [&]() {
        if (position < tokens.size() && tokens[position] == "NOT") {
            ++position;
            set<int> result = allDocuments();
            const set<int> excluded = readNot();
            for (int id : excluded) {
                result.erase(id);
            }
            return result;
        }
        return readPrimary();
    };

    readAnd = [&]() {
        set<int> result = readNot();
        while (position < tokens.size() && tokens[position] == "AND") {
            ++position;
            const set<int> right = readNot();
            set<int> intersection;
            set_intersection(result.begin(), result.end(),
                             right.begin(), right.end(),
                             inserter(intersection, intersection.begin()));
            result = intersection;
        }
        return result;
    };

    readOr = [&]() {
        set<int> result = readAnd();
        while (position < tokens.size() && tokens[position] == "OR") {
            ++position;
            const set<int> right = readAnd();
            result.insert(right.begin(), right.end());
        }
        return result;
    };

    set<int> result = readOr();
    if (position != tokens.size()) {
        throw invalid_argument("Unexpected token: " + tokens[position]);
    }
    return result;
}
