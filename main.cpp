#include <iostream>
#include <fstream>
#include "huffmanEncoder.h"

int main() {
    //std::string test = "zzzzzxxxxyyya";
    //std::string test = "1234567890 abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ !@#$%^&*()_+";
    std::string test = "zzzzzzzzzz The quick brown fox jumps over the lazy dog. abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ !@#$%^&*()_+";
    //std::string test = "testtestt_1est";
    //std::string test = "aaaa bbb cccc ddddd";
    //std::string test = "0123456789 abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ !@#$%^&*()_+";
    std::cout << "test string: " << test << std::endl;
    HuffmanEncoder huffmanEnc = HuffmanEncoder(test);
    std::ofstream outputFile;
    outputFile.open("encoded.txt", std::ios::binary);
    huffmanEnc.encode(outputFile);
    outputFile.close();
    std::ifstream inputFile;
    inputFile.open("encoded.txt", std::ios::binary);
    outputFile.open("decoded.txt", std::ios::binary);
    huffmanEnc.decode(inputFile, outputFile);
    inputFile.close();
    outputFile.close();
    return 0;
}
