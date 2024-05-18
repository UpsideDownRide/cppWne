#ifndef HUFFMANDECODER_H
#define HUFFMANDECODER_H

#include <iostream>
#include "huffmanNode.h"
#include "fileHeader.h"

class HuffmanDecoder {
    private:
        HuffmanNode *root;
        HuffmanNode *current;
        std::istream &input;
        std::ostream &output;

    public:
        HuffmanDecoder(std::istream &input, std::ostream &output) : input(input), output(output) {};
        void decode();
};        

#endif // HUFFMANDECODER_H

#ifndef BITREADER_H
#define BITREADER_H

class BitReader {
    private:
        std::istream &input;
        uint8_t buffer;
        uint8_t index;
    public:
        BitReader(std::istream &input);
        bool readBit();
        char readChar();
};

#endif // BITREADER_H
