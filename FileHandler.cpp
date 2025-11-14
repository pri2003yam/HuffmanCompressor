#include "FileHandler.h"
#include <fstream>
#include <stdexcept>
#include <vector>

std::vector<unsigned char> FileHandler::readBinary(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("Failed to open input file.");

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<unsigned char> buffer(size);
    file.read(reinterpret_cast<char*>(buffer.data()), size);
    return buffer;
}

void FileHandler::writeBinary(const std::string& path, const std::vector<unsigned char>& data) {
    std::ofstream file(path, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("Failed to open output file.");

    file.write(reinterpret_cast<const char*>(data.data()), data.size());
}
