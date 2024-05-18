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
        uint8_t buffer;
        uint8_t index;
        std::istream &input;
        size_t toProcess;
    public:
        BitReader(std::istream &input);
        bool readBit();
        char readChar();
        bool done();
};

#endif // BITREADER_H
