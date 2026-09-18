#include "BooleanQuery.h"
#include "DocumentReader.h"
#include "IncidenceMatrix.h"
#include "InvertedIndex.h"
#include "TextProcessor.h"

#include <chrono>
#include <iostream>
#include <string>

using namespace std;

void printDocuments(const vector<Document>& documents) {
    cout << "Documents\n";
    for (const auto& document : documents) {
        cout << "  D" << document.id << " -> " << document.name << '\n';
    }
}

void printIndex(const InvertedIndex& index) {
    cout << "\nInverted index (term: document [frequency])\n";
    for (const auto& [term, postings] : index.entries()) {
        cout << "  " << term << ": ";
        for (const PostingList::Node* current = postings.head(); current != nullptr;
             current = current->next) {
            cout << "D" << current->value.documentId << " ["
                 << current->value.frequency << "] ";
        }
        cout << '\n';
    }
}

void printResults(const set<int>& result, const vector<Document>& documents) {
    if (result.empty()) {
        cout << "No matching documents.\n";
        return;
    }

    cout << "Matching documents: ";
    for (int id : result) {
        cout << "D" << id << " (" << documents[id - 1].name << ") ";
    }
    cout << '\n';
}

int main(int argc, char* argv[]) {
    const string dataPath = argc > 1 ? argv[1] : "data";

    try {
        DocumentReader reader;
        TextProcessor processor;
        const auto documents = reader.readDirectory(dataPath);

        if (documents.empty()) {
            cout << "No .txt documents were found in: " << dataPath << '\n';
            return 0;
        }

        InvertedIndex index;
        for (const auto& document : documents) {
            index.addDocument(document.id, processor.tokenize(document.content));
        }

        printDocuments(documents);
        printIndex(index);

        IncidenceMatrix matrix;
        matrix.build(index, static_cast<int>(documents.size()));
        matrix.print();

        BooleanQuery queryEngine(index, static_cast<int>(documents.size()));
        cout << "\nTry a Boolean query (example: search AND engine)\n";
        cout << "Type exit to stop.\n";

        string query;
        while (cout << "> " && getline(cin, query) && query != "exit") {
            try {
                const auto start = chrono::steady_clock::now();
                const set<int> result = queryEngine.evaluate(query);
                const auto end = chrono::steady_clock::now();

                printResults(result, documents);

                const auto microseconds =
                    chrono::duration_cast<chrono::microseconds>(end - start);
                cout << "Query time: " << microseconds.count() << " us\n";
            } catch (const invalid_argument& error) {
                cout << "Invalid query: " << error.what() << '\n';
            }
        }
    } catch (const exception& error) {
        cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
