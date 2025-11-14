#include "Compressor.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>

// -----------------------------------------------------------------------------
// BUILD FREQUENCY TABLE
// -----------------------------------------------------------------------------
std::unordered_map<unsigned char, uint64_t> Compressor::buildFrequencyTable(const std::vector<unsigned char> &data)
{
    std::unordered_map<unsigned char, uint64_t> freq;
    for (unsigned char c : data)
        freq[c]++;
    return freq;
}

// -----------------------------------------------------------------------------
// ENCODE DATA USING GENERATED HUFFMAN CODES
// -----------------------------------------------------------------------------
std::vector<unsigned char> Compressor::encode(
    const std::vector<unsigned char> &data,
    const std::unordered_map<unsigned char, std::string> &codes,
    uint64_t &bitLength)
{
    std::vector<unsigned char> encodedBytes;
    unsigned char buffer = 0;
    int bitCount = 0;
    bitLength = 0;

    for (unsigned char c : data)
    {
        const std::string &code = codes.at(c);
        for (char bit : code)
        {
            buffer = (buffer << 1) | (bit == '1');
            bitCount++;

            if (bitCount == 8)
            {
                encodedBytes.push_back(buffer);
                bitCount = 0;
                buffer = 0;
            }

            // increment AFTER handling possible byte flush to avoid off-by-one
            bitLength++;
        }
    }

    if (bitCount > 0)
    { // pad remaining bits if not byte-aligned
        buffer <<= (8 - bitCount);
        encodedBytes.push_back(buffer);
    }
    return encodedBytes;
}

// -----------------------------------------------------------------------------
// COMPRESS FILE
// -----------------------------------------------------------------------------
void Compressor::compress(const std::string &inputFile, const std::string &outputFile)
{
    auto data = FileHandler::readBinary(inputFile);
    if (data.empty())
        throw std::runtime_error("Input file is empty.");

    auto freq = buildFrequencyTable(data);
    tree.buildTree(freq);
    const auto &codes = tree.getCodes();

    uint64_t bitLength = 0;
    auto encoded = encode(data, codes, bitLength);

    std::ofstream out(outputFile, std::ios::binary);
    if (!out.is_open())
        throw std::runtime_error("Failed to open output file.");

    // --- HEADER ---
    uint16_t symbolCount = static_cast<uint16_t>(freq.size());
    out.write(reinterpret_cast<const char*>(&symbolCount), sizeof(symbolCount));
    for (auto &[ch, f] : freq)
    {
        out.write(reinterpret_cast<const char*>(&ch), sizeof(ch));
        out.write(reinterpret_cast<const char*>(&f), sizeof(f));
    }
    out.write(reinterpret_cast<const char*>(&bitLength), sizeof(bitLength));

    // --- BODY ---
    if (!encoded.empty())
        out.write(reinterpret_cast<const char*>(encoded.data()), encoded.size());
    out.close();

    std::cout << "Compression complete. Encoded bits: " << bitLength << "\n";
}

// -----------------------------------------------------------------------------
// DECODE BINARY STREAM BACK TO ORIGINAL BYTES
// -----------------------------------------------------------------------------
std::vector<unsigned char> Compressor::decode(
    const std::vector<unsigned char> &encodedBytes,
    Node *root,
    uint64_t bitLength)
{
    std::vector<unsigned char> decoded;
    if (!root) return decoded;

    Node *current = root;
    uint64_t bitsRead = 0;

    for (unsigned char byte : encodedBytes)
    {
        for (int i = 7; i >= 0; --i)
        {
            if (bitsRead >= bitLength)
                return decoded; // stop immediately if we've read all meaningful bits

            bool bit = (byte >> i) & 1;
            current = bit ? current->right : current->left;

            if (!current->left && !current->right) // leaf node
            {
                decoded.push_back(current->data);
                current = root;

                // if we've just completed the last symbol, exit
                if (bitsRead + 1 >= bitLength)
                    return decoded;
            }

            bitsRead++;
        }
    }

    return decoded;
}

// -----------------------------------------------------------------------------
// DECOMPRESS FILE
// -----------------------------------------------------------------------------
void Compressor::decompress(const std::string &inputFile, const std::string &outputFile)
{
    std::ifstream in(inputFile, std::ios::binary);
    if (!in.is_open())
        throw std::runtime_error("Failed to open compressed file.");

    // --- READ HEADER ---
    uint16_t symbolCount = 0;
    in.read(reinterpret_cast<char*>(&symbolCount), sizeof(symbolCount));

    std::unordered_map<unsigned char, uint64_t> freqTable;
    for (int i = 0; i < symbolCount; ++i)
    {
        unsigned char ch;
        uint64_t freq;
        in.read(reinterpret_cast<char*>(&ch), sizeof(ch));
        in.read(reinterpret_cast<char*>(&freq), sizeof(freq));
        freqTable[ch] = freq;
    }

    uint64_t bitLength = 0;
    in.read(reinterpret_cast<char*>(&bitLength), sizeof(bitLength));

    // --- READ ENCODED BODY ---
    std::vector<unsigned char> encodedBytes(
        (std::istreambuf_iterator<char>(in)),
        std::istreambuf_iterator<char>());
    in.close();

    // --- REBUILD HUFFMAN TREE ---
    HuffmanTree decodeTree;
    decodeTree.buildTree(freqTable);
    Node *root = decodeTree.getRoot();

    // --- DECODE BACK TO ORIGINAL DATA ---
    auto decodedData = decode(encodedBytes, root, bitLength);

    // --- WRITE RESTORED OUTPUT FILE ---
    FileHandler::writeBinary(outputFile, decodedData);

    std::cout << "Decompression complete. Restored bytes: " << decodedData.size() << "\n";
}
