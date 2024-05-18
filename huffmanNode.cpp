// Klasa HuffmanNode reprezentuje węzeł drzewa Huffmana.
#include "huffmanNode.h"

// Konstruktor klasy HuffmanNode przyjmujący znak i częstość występowania.
HuffmanNode::HuffmanNode(char character, size_t frequency) : 
    HuffmanNode(character, frequency, nullptr, nullptr) {}

// Przeciążony konstruktor klasy HuffmanNode przyjmujący znak, częstość występowania oraz wskaźniki na lewe i prawe dziecko.
HuffmanNode::HuffmanNode(char character, size_t frequency, HuffmanNode *left, HuffmanNode *right) : 
    character(character), frequency(frequency), left(left), right(right) {}

// Destruktor klasy HuffmanNode usuwający wskazania na lewe i prawe dziecko.
HuffmanNode::~HuffmanNode() {
    delete left;
    delete right;
}

// Klasa pomocnicza służaca do przyrównywania węzłów drzewa Huffmana.
bool CompareHuffmanNodes::operator()(HuffmanNode *left, HuffmanNode *right) {
    return (left -> frequency > right -> frequency);
}