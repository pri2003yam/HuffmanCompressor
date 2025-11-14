#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "HuffmanTree.h"
#include "FileHandler.h"
#include <unordered_map>
#include <vector>
#include <string>

class Compressor {
private:
    HuffmanTree tree;

    std::unordered_map<unsigned char, uint64_t> buildFrequencyTable(const std::vector<unsigned char>& data);
    std::vector<unsigned char> encode(const std::vector<unsigned char>& data,
                                      const std::unordered_map<unsigned char, std::string>& codes,
                                      uint64_t& bitLength);
    std::vector<unsigned char> decode(const std::vector<unsigned char>& encodedBytes,
                                      Node* root,
                                      uint64_t bitLength);

public:
    void compress(const std::string& inputFile, const std::string& outputFile);
    void decompress(const std::string& inputFile, const std::string& outputFile);
};

#endif
