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
    std::ostream& encode(const std::string &input, std::ostream &output);
    void printCodes(std::unordered_map<char, uint8_t> codes);
    HuffmanNode *buildTree(std::unordered_map<char, size_t> frequencyMap);
    std::unordered_map<char, size_t> buildFrequencyMap(std::string text);
    void generateCodes(HuffmanNode *root, uint8_t code);

public:
    Huffman(std::string toEncode);
    std::ostream& encode(std::ostream &output);
    std::ostream& decode(const std::string &input, std::ostream &output);
};

#endif // HUFFMAN_H 