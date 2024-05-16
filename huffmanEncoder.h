#ifndef HUFFMANENCODER_H
#define HUFFMANENCODER_H

#include <string>
#include <queue>
#include <unordered_map>
#include <iostream>
#include "huffmanNode.h"
#include <cstdint>
#include <bitset>
#include <cmath>
#include "huffmanDecoder.h"

struct CodeWithLength {
    uint8_t code;
    size_t bitlength;
};

class HuffmanEncoder {
private:
    std::string toEncode;
    std::string encoded;
    HuffmanNode *root;
    std::unordered_map<char, size_t> frequencyMap;
    std::unordered_map<char, CodeWithLength> codes;
    
    void encode(const std::string &input, std::ostream &output);
    void printCodes(std::unordered_map<char, CodeWithLength> codes);
    HuffmanNode *buildTree(std::unordered_map<char, size_t> frequencyMap);
    void buildFrequencyMap(std::string text);
    void generateCodes(HuffmanNode *root);
    void generateCodes(HuffmanNode *root, uint8_t code);

public:
    HuffmanEncoder(std::string toEncode);
    void encode(std::ostream &output);
    void decode(std::istream &input,std::ostream &output);
};
#endif // HUFFMANENCODER_H 

#ifndef BITWRITER_H
#define BITWRITER_H

class BitWriter {
    private:
        uint8_t buffer;
        uint8_t index;
        std::ostream &output;
    public:
        BitWriter(std::ostream &output) : output(output), buffer(0), index(0) {}
        void writeBit(bool bit);
        void flush();
        
};

#endif // BITWRITER_H