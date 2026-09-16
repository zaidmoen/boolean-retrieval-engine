#include "DocumentReader.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <stdexcept>

namespace fs = std::filesystem;

std::string DocumentReader::readFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    return std::string((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
}

std::vector<Document> DocumentReader::readDirectory(
    const std::string& directoryPath) const {
    std::vector<fs::path> paths;

    if (!fs::exists(directoryPath) || !fs::is_directory(directoryPath)) {
        throw std::runtime_error("Data directory does not exist: " + directoryPath);
    }

    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            paths.push_back(entry.path());
        }
    }

    std::sort(paths.begin(), paths.end());

    std::vector<Document> documents;
    int id = 1;
    for (const auto& path : paths) {
        documents.push_back({id++, path.filename().string(), readFile(path.string())});
    }

    return documents;
}

