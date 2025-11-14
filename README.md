🌟 Huffman File Compressor
A lossless, high-performance file compression utility implemented in modern C++17






🚀 Overview

Huffman File Compressor is a lossless compression tool written in C++17, implementing the classic Huffman coding algorithm with fully deterministic tree construction.
It supports compression and decompression of any binary file while ensuring bit-accurate round-trip reconstruction.

This project demonstrates:

Real-world bit manipulation

Priority queue–based Huffman tree construction

Deterministic encoding to avoid decoding mismatches

Clean, modular object-oriented architecture

✨ Features

✔️ Lossless file compression using Huffman Coding

✔️ Fully deterministic tree building (consistent encode/decode)

✔️ Bit-level encoder/decoder for optimal space efficiency

✔️ Modular OOP design: Compressor, HuffmanTree, Node, FileHandler

✔️ Cross-platform (Windows/Linux)

✔️ Makefile-based compilation

🛠️ Tech Stack

Language: C++17

Libraries: STL (priority_queue, vectors, maps)

Tools: Makefile (MinGW / GCC), VS Code

Algorithms: Huffman Coding, Bit Packing

📦 Build Instructions
Compile
make

Clean Build Files
make clean

🔧 Usage
Compress a file
./compressor.exe --compress <input-file> <output-file.huf>


Example:

./compressor.exe --compress input.txt compressed.huf

Decompress a file
./compressor.exe --decompress <input-file.huf> <output-file>


Example:

./compressor.exe --decompress compressed.huf restored.txt

📂 Project Structure
HuffmanCompressor/
│
├── Compressor.cpp / .h      → Main compression/decompression logic
├── HuffmanTree.cpp / .h     → Tree building & code generation
├── Node.h                   → Node structure & stable comparator
├── FileHandler.cpp / .h     → Binary file read/write utilities
├── main.cpp                 → CLI interface (compress/decompress)
├── Makefile                 → Build script
└── README.md                → Project documentation

🧠 How It Works (Short Version)

Frequency Table
Counts byte frequencies from input file.

Huffman Tree Construction
Builds a deterministic min-heap based Huffman tree.

Encoding
Generates prefix-free codes and encodes file data bit-by-bit.

Bit Packing
Packs variable-length codes into bytes with proper padding.

Decoding
Reconstructs the tree and decodes the bitstream back to original bytes.

🖼️ Demo

(You can add screenshots here later if you want)

📜 License

MIT License — feel free to use and modify.

⭐ Like this project?

Leave a star ⭐ on the GitHub repo — it helps others discover the project!
