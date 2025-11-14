#include "HuffmanTree.h"

HuffmanTree::HuffmanTree() : root(nullptr) {}

HuffmanTree::~HuffmanTree() {
    freeTree(root);
}

void HuffmanTree::buildTree(const std::unordered_map<unsigned char, uint64_t>& freqTable) {
    std::priority_queue<Node*, std::vector<Node*>, NodeCompare> pq;

    for (auto& pair : freqTable)
        pq.push(new Node(pair.first, pair.second));

    if (pq.size() == 1) {
        // Edge case: only one character
        root = pq.top();
        codes[root->data] = "0";
        return;
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        // ✅ Ensure deterministic merge order for equal frequencies
        if (right->freq < left->freq || 
           (right->freq == left->freq && right->data < left->data))
            std::swap(left, right);

        Node* parent = new Node('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    root = pq.top();
    buildCodes(root, "");
}

void HuffmanTree::buildCodes(Node* node, const std::string& code) {
    if (!node) return;
    if (!node->left && !node->right) {
        codes[node->data] = code;
        return;
    }
    buildCodes(node->left, code + "0");
    buildCodes(node->right, code + "1");
}

const std::unordered_map<unsigned char, std::string>& HuffmanTree::getCodes() const {
    return codes;
}

Node* HuffmanTree::getRoot() const {
    return root;
}

void HuffmanTree::freeTree(Node* node) {
    if (!node) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}
