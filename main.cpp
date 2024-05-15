#include <iostream>
#include <sstream>
#include "huffman.h"

int main() {
    std::string test = "zzzzzxxxxyyya";
    //std::string test = "1234567890 abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ !@#$%^&*()_+";
    //std::string test = "zzzzzzzzzz The quick brown fox jumps over the lazy dog.";
    std::cout << "test string: " << test << std::endl;
    std::cout << "Initializing Huffman object..." << std::endl;
    Huffman huffman = Huffman(test);
    //huffman.encode(std::cout);
    std::stringstream ss;
    huffman.encode(ss);
    huffman.decode(ss.str(), std::cout);
    return 0;
}