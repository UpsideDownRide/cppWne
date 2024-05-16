#include "huffmanNode.h"

HuffmanNode::HuffmanNode(char character, size_t frequency) {
    this -> character = character;
    this -> frequency = frequency;
    this -> left = nullptr;
    this -> right = nullptr;
}

HuffmanNode::HuffmanNode(char character, size_t frequency, HuffmanNode *left, HuffmanNode *right) {
    this -> character = character;
    this -> frequency = frequency;
    this -> left = left;
    this -> right = right;
}

HuffmanNode::~HuffmanNode() {
    delete left;
    delete right;
}
    
std::ostream& operator<<(std::ostream &os, const HuffmanNode &node) {
    os << node.character << ":" << node.frequency;
    return os;
}

bool CompareHuffmanNodes::operator()(HuffmanNode *left, HuffmanNode *right) {
    return (left -> frequency > right -> frequency);
}