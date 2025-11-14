#ifndef NODE_H
#define NODE_H

#include <cstdint>

struct Node {
    unsigned char data;   // Byte value (0–255)
    uint64_t freq;        // Frequency of the byte
    Node* left;           // Left child
    Node* right;          // Right child

    Node(unsigned char d, uint64_t f)
        : data(d), freq(f), left(nullptr), right(nullptr) {}
};

// Deterministic comparator for Huffman priority queue
struct NodeCompare {
    bool operator()(Node* a, Node* b) const {
        // Primary: smaller frequency has higher priority
        // Secondary: smaller ASCII value (data) has higher priority
        if (a->freq == b->freq)
            return a->data > b->data;  // ensures stable ordering
        return a->freq > b->freq;
    }
};

#endif
