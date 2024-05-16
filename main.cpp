#include <iostream>
#include <fstream>
#include "huffmanEncoder.h"

int main() {
    //std::string test = "zzzzzxxxxyyya";
    //std::string test = "1234567890 abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ !@#$%^&*()_+";
    //std::string test = "zzzzzzzzzz The quick brown fox jumps over the lazy dog.";
    //std::string test = "testtestt_1est";
    std::string test = "aaaa bbb cccc ddddd";
    std::cout << "test string: " << test << std::endl;
    std::cout << "Initializing Huffman object..." << std::endl;
    HuffmanEncoder huffmanEnc = HuffmanEncoder(test);
    //huffman.encode(std::cout);
    std::ofstream outputFile;
    outputFile.open("encoded.txt");
    huffmanEnc.encode(outputFile);
    outputFile.close();
    std::ifstream inputFile;
    inputFile.open("encoded.txt");
    huffmanEnc.decode(inputFile, std::cout);
    return 0;
}