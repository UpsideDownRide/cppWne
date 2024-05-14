#include <iostream>
#include "huffman.h"

int main() {
    std::string test = "zzzzzxxxxyyya";
    std::cout << "test string: " << test << std::endl;
    std::cout << "Initializing Huffman object..." << std::endl;
    Huffman huffman = Huffman(test); 
    std::cout << "initializing frequency map..." << std::endl; 
    std::unordered_map<char, size_t> freq = huffman.buildFrequencyMap(test);
    
    for (auto pair : freq) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }

    std::cout << "building tree..." << std::endl;
    HuffmanNode *huffmanRoot = huffman.buildTree(freq);

    std::cout << "generating codes..." << std::endl;
    std::unordered_map<char, std::string> codes;
    huffman.generateCodes(huffmanRoot, "", codes);

    std::cout << "printing codes..." << std::endl;
    huffman.printCodes(codes);

    return 0;
}