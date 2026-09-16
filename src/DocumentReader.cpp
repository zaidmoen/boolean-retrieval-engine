#include "DocumentReader.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <stdexcept>

using namespace std;
namespace fs = filesystem;

string DocumentReader::readFile(const string& filePath) {
    ifstream file(filePath);
    if (!file) {
        throw runtime_error("Could not open file: " + filePath);
    }

    return string((istreambuf_iterator<char>(file)),
                  istreambuf_iterator<char>());
}

vector<Document> DocumentReader::readDirectory(const string& directoryPath) const {
    vector<fs::path> paths;

    if (!fs::exists(directoryPath) || !fs::is_directory(directoryPath)) {
        throw runtime_error("Data directory does not exist: " + directoryPath);
    }

    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            paths.push_back(entry.path());
        }
    }

    sort(paths.begin(), paths.end());

    vector<Document> documents;
    int id = 1;
    for (const auto& path : paths) {
        documents.push_back({id++, path.filename().string(), readFile(path.string())});
    }

    return documents;
}
