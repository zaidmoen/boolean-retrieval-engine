#include "IncidenceMatrix.h"

#include <iomanip>
#include <iostream>

using namespace std;

void IncidenceMatrix::build(const InvertedIndex& index, int documentCount) {
    rowTerms = index.terms();
    values.assign(rowTerms.size(), vector<int>(documentCount, 0));

    for (size_t row = 0; row < rowTerms.size(); ++row) {
        const PostingList* postings = index.find(rowTerms[row]);
        for (const PostingList::Node* current = postings->head(); current != nullptr;
             current = current->next) {
            values[row][current->value.documentId - 1] = 1;
        }
    }
}

void IncidenceMatrix::print() const {
    cout << "\nTerm-document incidence matrix\n";
        cout << left << setw(16) << "Term";

    if (!values.empty()) {
        for (size_t document = 0; document < values.front().size(); ++document) {
            cout << setw(7) << "D" + to_string(document + 1);
        }
    }
    cout << '\n';

    for (size_t row = 0; row < rowTerms.size(); ++row) {
        cout << left << setw(16) << rowTerms[row];
        for (int value : values[row]) {
            cout << setw(7) << value;
        }
        cout << '\n';
    }
}
