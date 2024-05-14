#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <queue>
#include <unordered_map>
#include <iostream>
#include "huffmanNode.h"

class Huffman {
private:
    std::string toEncode;
    std::string encoded;
    HuffmanNode *root;
    std::unordered_map<char, size_t> frequencyMap;
    std::unordered_map<char, std::string> codes;
    friend std::ostream& operator<<(std::ostream &os, const Huffman &huffman);

public:
    Huffman(std::string toEncode);
    std::string encode(const std::string &input);
    std::string decode(const std::string &input);
    void printCodes(std::unordered_map<char, std::string> codes);
    HuffmanNode *buildTree(std::unordered_map<char, size_t> frequencyMap);
    std::unordered_map<char, size_t> buildFrequencyMap(std::string text);
    std::unordered_map<char, std::string> generateCodes(HuffmanNode *root, std::string code, std::unordered_map<char, std::string>& codes);
};

#endif // HUFFMAN_H 