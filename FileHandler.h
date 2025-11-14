#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>
#include <cstdint>

class FileHandler {
public:
    static std::vector<unsigned char> readBinary(const std::string& path);
    static void writeBinary(const std::string& path, const std::vector<unsigned char>& data);
};

#endif
