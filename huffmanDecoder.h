#ifndef HUFFMANDECODER_H
#define HUFFMANDECODER_H

#include <iostream>
#include "huffmanNode.h"
#include "fileHeader.h"

class HuffmanDecoder {
    private:
        HuffmanNode *root;
        HuffmanNode *current;
    public:
        HuffmanDecoder(HuffmanNode *root) : root(root), current(nullptr) {};
        void decode(std::istream &input, std::ostream &output);
};        

#endif // HUFFMANDECODER_H
