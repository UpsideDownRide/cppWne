#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <queue>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include "huffmanNode.h"
#include <cstdint>
#include <bitset>

class Huffman {
private:
    std::string toEncode;
    std::string encoded;
    HuffmanNode *root;
    std::unordered_map<char, size_t> frequencyMap;
    std::unordered_map<char, uint8_t> codes;
    friend std::ostream& operator<<(std::ostream &os, const Huffman &huffman);
    std::ostream& encode(const std::string &input, std::ostream &output);
    void printCodes(std::unordered_map<char, uint8_t> codes);
    HuffmanNode *buildTree(std::unordered_map<char, size_t> frequencyMap);
    std::unordered_map<char, size_t> buildFrequencyMap(std::string text);
    void generateCodes(HuffmanNode *root, uint8_t code);

public:
    Huffman(std::string toEncode);
    std::ostream& encode(std::ostream &output);
    void decode(const std::string &input, std::ostream &output);
};

#endif // HUFFMAN_H 