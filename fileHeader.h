#ifndef HEADER_H
#define HEADER_H
#include <cstdint>
#include <iostream>

struct fileHeader {
    uint16_t treeLength;
    size_t encodingLength;
};

#endif // HEADER_H