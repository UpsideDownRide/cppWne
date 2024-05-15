#ifndef HUFFMANNODE_H
#define HUFFMANNODE_H

#include <iostream>
#include <cstdint>

struct HuffmanNode {
    uint8_t code;
    size_t frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(uint8_t code, size_t frequency);
    HuffmanNode(uint8_t code, size_t frequency, HuffmanNode *left, HuffmanNode *right);
    ~HuffmanNode();
};

struct CompareHuffmanNodes {
    bool operator()(HuffmanNode *left, HuffmanNode *right); 
};

std::ostream& operator<<(std::ostream &os, const HuffmanNode &node);

#endif // HUFFMANNODE_H