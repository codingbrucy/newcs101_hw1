#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>

// Node structure to store each word and its frequency.
struct Node {
    std::string word;  // The word itself
    int freq;          // Frequency count for this word
    Node* next;        // Pointer to the next node

    // Constructor: initializes word, sets frequency to 1, and next pointer to nullptr.
    Node(const std::string& w) : word(w), freq(1), next(nullptr) {}
};

class LinkedList {
public:
    // Constructor: initializes an empty list.
    LinkedList();

    // Destructor: frees all allocated nodes.
    ~LinkedList();

    // Inserts a word into the linked list in lexicographical order.
    // If the word already exists, its frequency is incremented.
    void insert_in_order(const std::string& word);

    // Searches for the node containing the given word.
    // Returns a pointer to the node if found, otherwise returns nullptr.
    Node* search(const std::string& word);

    // Returns the number of unique words stored in the list.
    int size() const;

    // Returns the head pointer of the list.
    Node* getHead() const;

    // Optional: Sorts the linked list by frequency in descending order.
    // In case of ties, the order remains lexicographical.
    void sort_by_frequency();

    void reverse(){// working rever 
        if(!head || !(head->next)) return; // empty list or list of 1 elem
        Node* pre = head;
        Node* post = head->next;
        while(post){
            Node* temp = post->next;
            post->next = head;
            pre->next = temp;
            head = post;
            post = temp;
        }
    }

private:
    Node* head;  // Pointer to the head of the linked list

    // Helper functions for merge sort used in sort_by_frequency.
    Node* mergeSort(Node* node);
    Node* sortedMerge(Node* a, Node* b);
    void splitList(Node* source, Node** frontRef, Node** backRef);
};

#endif // LINKEDLIST_H