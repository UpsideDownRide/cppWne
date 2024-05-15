#include "huffmanNode.h"

HuffmanNode::HuffmanNode(uint8_t code, size_t frequency) {
    this -> code = code;
    this -> frequency = frequency;
    this -> left = nullptr;
    this -> right = nullptr;
}

HuffmanNode::HuffmanNode(uint8_t code, size_t frequency, HuffmanNode *left, HuffmanNode *right) {
    this -> code = code;
    this -> frequency = frequency;
    this -> left = left;
    this -> right = right;
}

HuffmanNode::~HuffmanNode() {
    delete left;
    delete right;
}
    
std::ostream& operator<<(std::ostream &os, const HuffmanNode &node) {
    os << node.code << ":" << node.frequency;
    return os;
}

bool CompareHuffmanNodes::operator()(HuffmanNode *left, HuffmanNode *right) {
    return (left -> frequency > right -> frequency);
}