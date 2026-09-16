#include "BooleanQuery.h"
#include "DocumentReader.h"
#include "IncidenceMatrix.h"
#include "InvertedIndex.h"
#include "TextProcessor.h"

#include <iostream>
#include <string>

void printDocuments(const std::vector<Document>& documents) {
    std::cout << "Documents\n";
    for (const auto& document : documents) {
        std::cout << "  D" << document.id << " -> " << document.name << '\n';
    }
}

void printIndex(const InvertedIndex& index) {
    std::cout << "\nInverted index (term: document [frequency])\n";
    for (const auto& [term, postings] : index.entries()) {
        std::cout << "  " << term << ": ";
        for (const auto& [documentId, frequency] : postings) {
            std::cout << "D" << documentId << " [" << frequency << "] ";
        }
        std::cout << '\n';
    }
}

void printResults(const std::set<int>& result,
                  const std::vector<Document>& documents) {
    if (result.empty()) {
        std::cout << "No matching documents.\n";
        return;
    }

    std::cout << "Matching documents: ";
    for (int id : result) {
        std::cout << "D" << id << " (" << documents[id - 1].name << ") ";
    }
    std::cout << '\n';
}

int main(int argc, char* argv[]) {
    const std::string dataPath = argc > 1 ? argv[1] : "data";

    try {
        DocumentReader reader;
        TextProcessor processor;
        const auto documents = reader.readDirectory(dataPath);

        if (documents.empty()) {
            std::cout << "No .txt documents were found in: " << dataPath << '\n';
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
        std::cout << "\nTry a Boolean query (example: search AND engine)\n";
        std::cout << "Type exit to stop.\n";

        std::string query;
        while (std::cout << "> " && std::getline(std::cin, query) && query != "exit") {
            printResults(queryEngine.evaluate(query), documents);
        }
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}

