#include "LinkedList.h"

using namespace std;

PostingList::PostingList() : first(nullptr), last(nullptr) {}

PostingList::PostingList(const PostingList& other) : first(nullptr), last(nullptr) {
    for (const Node* current = other.head(); current != nullptr; current = current->next) {
        Node* copy = new Node{current->value, nullptr};
        if (first == nullptr) {
            first = copy;
        } else {
            last->next = copy;
        }
        last = copy;
    }
}

PostingList& PostingList::operator=(const PostingList& other) {
    if (this == &other) {
        return *this;
    }

    clear();
    for (const Node* current = other.head(); current != nullptr; current = current->next) {
        add(current->value.documentId);
        last->value.frequency = current->value.frequency;
    }
    return *this;
}

PostingList::~PostingList() {
    clear();
}

void PostingList::add(int documentId) {
    if (last != nullptr && last->value.documentId == documentId) {
        last->value.frequency++;
        return;
    }

    Node* newNode = new Node{{documentId, 1}, nullptr};
    if (first == nullptr) {
        first = newNode;
    } else {
        last->next = newNode;
    }
    last = newNode;
}

const PostingList::Node* PostingList::head() const {
    return first;
}

void PostingList::clear() {
    while (first != nullptr) {
        Node* next = first->next;
        delete first;
        first = next;
    }
    last = nullptr;
}

