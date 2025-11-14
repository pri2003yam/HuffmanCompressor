#include "Compressor.h"
#include <iostream>

int main(int argc, char* argv[]) {
    Compressor compressor;

    if (argc < 4) {
        std::cout << "Usage:\n";
        std::cout << "  compressor --compress <input> <output>\n";
        std::cout << "  compressor --decompress <input> <output>\n";
        return 0;
    }

    std::string mode = argv[1];
    std::string input = argv[2];
    std::string output = argv[3];

    try {
        if (mode == "--compress") {
            compressor.compress(input, output);
            std::cout << "File compressed successfully.\n";
        } 
        else if (mode == "--decompress") {
            compressor.decompress(input, output);
            std::cout << "File decompressed successfully.\n";
        } 
        else {
            std::cerr << "Invalid mode. Use --compress or --decompress.\n";
        }
    } 
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
