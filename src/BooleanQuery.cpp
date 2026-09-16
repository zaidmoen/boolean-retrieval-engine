#include "BooleanQuery.h"

#include <algorithm>
#include <cctype>
#include <sstream>
#include <vector>

BooleanQuery::BooleanQuery(const InvertedIndex& index, int documentCount)
    : index(index), documentCount(documentCount) {}

std::vector<std::string> BooleanQuery::split(const std::string& query) {
    std::istringstream stream(query);
    std::vector<std::string> tokens;
    std::string token;

    while (stream >> token) {
        for (char& character : token) {
            character = static_cast<char>(std::toupper(static_cast<unsigned char>(character)));
        }
        tokens.push_back(token);
    }
    return tokens;
}

std::set<int> BooleanQuery::allDocuments() const {
    std::set<int> result;
    for (int id = 1; id <= documentCount; ++id) {
        result.insert(id);
    }
    return result;
}

std::set<int> BooleanQuery::documentsForTerm(const std::string& term) const {
    std::string normalized = term;
    std::transform(normalized.begin(), normalized.end(), normalized.begin(),
                   [](unsigned char character) {
                       return static_cast<char>(std::tolower(character));
                   });

    std::set<int> result;
    const PostingList* postings = index.find(normalized);
    if (postings == nullptr) {
        return result;
    }

    for (const auto& [documentId, frequency] : *postings) {
        (void)frequency;
        result.insert(documentId);
    }
    return result;
}

std::set<int> BooleanQuery::evaluate(const std::string& query) const {
    const auto tokens = split(query);
    if (tokens.empty()) {
        return {};
    }

    std::size_t position = 0;
    auto readOperand = [&]() {
        bool negated = false;
        if (position < tokens.size() && tokens[position] == "NOT") {
            negated = true;
            ++position;
        }

        if (position >= tokens.size()) {
            return std::set<int>{};
        }

        std::set<int> operand = documentsForTerm(tokens[position++]);
        if (negated) {
            std::set<int> complement = allDocuments();
            for (int id : operand) {
                complement.erase(id);
            }
            return complement;
        }
        return operand;
    };

    std::set<int> result = readOperand();
    while (position < tokens.size()) {
        const std::string operation = tokens[position++];
        if (operation != "AND" && operation != "OR") {
            continue;
        }

        const std::set<int> current = readOperand();
        if (operation == "AND") {
            std::set<int> intersection;
            std::set_intersection(result.begin(), result.end(), current.begin(),
                                  current.end(),
                                  std::inserter(intersection, intersection.begin()));
            result = intersection;
        } else {
            result.insert(current.begin(), current.end());
        }
    }

    return result;
}
