#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "Node.h"
#include <unordered_map>
#include <queue>
#include <string>

class HuffmanTree {
private:
    Node* root;
    std::unordered_map<unsigned char, std::string> codes;

    void buildCodes(Node* node, const std::string& code);

public:
    HuffmanTree();
    ~HuffmanTree();

    void buildTree(const std::unordered_map<unsigned char, uint64_t>& freqTable);
    const std::unordered_map<unsigned char, std::string>& getCodes() const;
    Node* getRoot() const;
    void freeTree(Node* node);
};

#endif
