#include "huffmanDecoder.h"

inline fileHeader processHeader(std::istream &input) {
    fileHeader header;
    input.read(reinterpret_cast<char*>(&header.treeLength), sizeof(header.treeLength));
    input.read(reinterpret_cast<char*>(&header.encodingLength), sizeof(header.encodingLength));
    return header;
}

void HuffmanDecoder::decode(std::istream &input, std::ostream &output) {
    HuffmanNode *current = this->root;
    char* byte = new char[1];
    fileHeader header;
    std::cout << "decoding..." << std::endl;
    if (input.good()) {
        header = processHeader(input);
    }

    size_t processed = 0;

    while (!input.eof() && processed <= header.encodingLength) {
        input.read(byte, 1);
        for (int i = 7; i >= 0 && processed <= header.encodingLength; i--, processed++) {
            bool bit = (byte[0] >> i) & 1;
            if (bit) {
                current = (current->right);
            } else {
                current = (current->left);
            }
            if (current -> left == nullptr && current -> right == nullptr) {
                output << current -> character;
                current = this->root;
            }
        }
    }
    return;
}