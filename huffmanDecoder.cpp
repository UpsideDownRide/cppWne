#include "huffmanDecoder.h"

inline fileHeader processHeader(std::istream &input) {
    fileHeader header;
    input.read(reinterpret_cast<char*>(&header.encodingLength), sizeof(header.encodingLength));
    return header;
}

HuffmanNode* generateTree(BitReader &reader) {
    if (reader.readBit()) {
        char character = reader.readChar();
        return new HuffmanNode(character, 0);
    } else {
        HuffmanNode *left = generateTree(reader);
        HuffmanNode *right = generateTree(reader);
        return new HuffmanNode('\0', 0, left, right);
    }
}

void HuffmanDecoder::decode() {
    char* byte = new char[1];
    fileHeader header;
    
    std::cout << "decoding..." << std::endl;
    
    if (input.good()) {
        header = processHeader(input);
        std::cout << "header.encodingLength: " << header.encodingLength << std::endl;
    } else {
        std::cout << "Error with the input" << std::endl;
        return;
    }
    
    BitReader reader = BitReader(input);
    root = generateTree(reader);
    current = root;

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

BitReader::BitReader(std::istream &input) : input(input), buffer(0), index(0) {
    input.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
}

bool BitReader::readBit() {
    bool bit = (buffer >> (7 - index)) & 1;
    if (++index == 8) {
        input.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
        index = 0;
    }
    toProcess--;
    return bit;
}

char BitReader::readChar() {
    char character = 0;
    for (int i = 7; i >= 0; i--) {
        character |= (readBit() << i);
        toProcess--;
    }
    return character;
}

bool BitReader::done() {
    return toProcess == 0;
}