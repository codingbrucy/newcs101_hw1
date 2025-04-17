// LinkedList.h
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>

// Node structure: holds a word, its frequency, and a next pointer
struct Node {
    std::string word;
    int freq;
    Node* next;
    Node(const std::string& w) : word(w), freq(1), next(nullptr) {}
};

// LinkedList: stores Nodes in lexicographical order, tracks frequencies, and can sort by freq
class LinkedList {
public:
    LinkedList() : head(nullptr) {}
    ~LinkedList() {
        Node* cur = head;
        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
    }

    // Insert word in lex order; increment freq if it already exists
    void insert_in_order(const std::string& w) {
        if (!head) {
            head = new Node(w);
            return;
        }
        Node* prev = nullptr;
        Node* cur = head;
        while (cur && cur->word < w) {
            prev = cur;
            cur = cur->next;
        }
        if (cur && cur->word == w) {
            cur->freq++;
            return;
        }
        Node* n = new Node(w);
        n->next = cur;
        if (prev)
            prev->next = n;
        else
            head = n;
    }

    // Find node by word
    Node* search(const std::string& w) {
        Node* cur = head;
        while (cur) {
            if (cur->word == w)
                return cur;
            cur = cur->next;
        }
        return nullptr;
    }

    // Count unique words
    int size() const {
        int cnt = 0;
        Node* cur = head;
        while (cur) {
            cnt++;
            cur = cur->next;
        }
        return cnt;
    }

    // Access head for iteration
    Node* getHead() const { return head; }

    // Sort list by descending frequency (tie: lex order)
    void sort_by_frequency() { head = mergeSort(head); }

private:
    Node* head;

    // Merge sort utilities
    Node* mergeSort(Node* h) {
        if (!h || !h->next) return h;
        Node* a; Node* b;
        splitList(h, &a, &b);
        a = mergeSort(a);
        b = mergeSort(b);
        return sortedMerge(a, b);
    }

    Node* sortedMerge(Node* a, Node* b) {
        if (!a) return b;
        if (!b) return a;
        if (a->freq > b->freq || (a->freq == b->freq && a->word < b->word)) {
            a->next = sortedMerge(a->next, b);
            return a;
        } else {
            b->next = sortedMerge(a, b->next);
            return b;
        }
    }

    void splitList(Node* src, Node** frontRef, Node** backRef) {
        Node* fast = src->next;
        Node* slow = src;
        while (fast) {
            fast = fast->next;
            if (fast) {
                slow = slow->next;
                fast = fast->next;
            }
        }
        *frontRef = src;
        *backRef = slow->next;
        slow->next = nullptr;
    }
};

#endif // LINKEDLIST_H