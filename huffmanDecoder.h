#ifndef HUFFMANDECODER_H
#define HUFFMANDECODER_H

#include <iostream>
#include "huffmanNode.h"

class HuffmanDecoder {
    private:
        HuffmanNode *root;
        HuffmanNode *current;
    public:
        HuffmanDecoder(HuffmanNode *root) : root(root) {};
        void decode(std::istream &input, std::ostream &output);
};        

#endif // HUFFMANDECODER_H
