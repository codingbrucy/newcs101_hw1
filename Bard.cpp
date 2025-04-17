// Bard.cpp
#include <iostream>
#include <fstream>
#include <string>
#include "LinkedList.h"

static const int MAX_LEN = 36;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <query_input> <output_file>\n";
        return 1;
    }

    // Prepare array of lists, one per word length
    LinkedList* lists[MAX_LEN + 1] = {nullptr};

    // Load Shakespeare words
    std::ifstream dict("shakespeare-cleaned5.txt");
    if (!dict) {
        std::cerr << "Error: cannot open shakespeare-cleaned5.txt\n";
        return 1;
    }
    std::string word;
    while (dict >> word) {
        int len = word.size();
        if (len <= MAX_LEN) {
            if (!lists[len])
                lists[len] = new LinkedList();
            lists[len]->insert_in_order(word);
        }
    }
    dict.close();

    // Sort each list by frequency descending
    for (int i = 0; i <= MAX_LEN; ++i) {
        if (lists[i])
            lists[i]->sort_by_frequency();
    }

    // Process queries
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    if (!fin) {
        std::cerr << "Error: cannot open " << argv[1] << "\n";
        return 1;
    }
    int L, K;
    while (fin >> L >> K) {
        if (L < 0 || L > MAX_LEN || !lists[L] || lists[L]->size() <= K) {
            fout << "-\n";
        } else {
            Node* cur = lists[L]->getHead();
            for (int i = 0; i < K; ++i) cur = cur->next;
            fout << cur->word << "\n";
        }
    }
    fin.close();
    fout.close();

    // Cleanup
    for (int i = 0; i <= MAX_LEN; ++i)
        delete lists[i];

    return 0;
}
