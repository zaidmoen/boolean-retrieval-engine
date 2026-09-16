#pragma once

#include <string>
#include <vector>

using namespace std;

struct Document {
    int id;
    string name;
    string content;
};

class DocumentReader {
public:
    vector<Document> readDirectory(const string& directoryPath) const;

private:
    static string readFile(const string& filePath);
};
