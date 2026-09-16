#pragma once

#include <string>
#include <vector>

struct Document {
    int id;
    std::string name;
    std::string content;
};

class DocumentReader {
public:
    std::vector<Document> readDirectory(const std::string& directoryPath) const;

private:
    static std::string readFile(const std::string& filePath);
};

