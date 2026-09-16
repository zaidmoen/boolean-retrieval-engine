#include "IncidenceMatrix.h"

#include <iomanip>
#include <iostream>

void IncidenceMatrix::build(const InvertedIndex& index, int documentCount) {
    rowTerms = index.terms();
    values.assign(rowTerms.size(), std::vector<int>(documentCount, 0));

    for (std::size_t row = 0; row < rowTerms.size(); ++row) {
        const PostingList* postings = index.find(rowTerms[row]);
        for (const auto& [documentId, frequency] : *postings) {
            (void)frequency;
            values[row][documentId - 1] = 1;
        }
    }
}

void IncidenceMatrix::print() const {
    std::cout << "\nTerm-document incidence matrix\n";
    std::cout << std::left << std::setw(16) << "Term";

    if (!values.empty()) {
        for (std::size_t document = 0; document < values.front().size(); ++document) {
            std::cout << std::setw(7) << "D" + std::to_string(document + 1);
        }
    }
    std::cout << '\n';

    for (std::size_t row = 0; row < rowTerms.size(); ++row) {
        std::cout << std::left << std::setw(16) << rowTerms[row];
        for (int value : values[row]) {
            std::cout << std::setw(7) << value;
        }
        std::cout << '\n';
    }
}

