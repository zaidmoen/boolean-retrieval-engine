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

    size_t size() const {
        size_t count = 0;
        for (const Node* current = first; current != nullptr; current = current->next) {
            ++count;
        }
        return count;
    }

private:
    void clear();
    Node* first;
    Node* last;
};
