#pragma once

#include <cstddef>

using namespace std;

struct Posting {
    int documentId;
    int frequency;
};

class PostingList {
public:
    struct Node {
        Posting value;
        Node* next;
    };

    PostingList();
    PostingList(const PostingList& other);
    PostingList& operator=(const PostingList& other);
    ~PostingList();

    void add(int documentId);
    const Node* head() const;

private:
    void clear();
    Node* first;
    Node* last;
};

