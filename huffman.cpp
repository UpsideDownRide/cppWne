#include <iostream>
#include <fstream>
#include <algorithm>
#include "huffmanEncoder.h"
#include "huffmanDecoder.h"

// Funkcja pomocnicza do pobierania opcji wywołania z linii poleceń
char* getOption (char** begin, char** end, const std::string &option) {
    char **it = std::find(begin, end, option);
    if (it != end && ++it != end) {
        return *it;
    }
    return 0;
}

// Funkcja pomocnicza do sprawdzania czy opcja wywołania istnieje
bool optionExists(char** begin, char** end, const std::string &option) {
    return std::find(begin, end, option) != end;
}

// Stałe reprezentujące opcje wywołania
std::string OUTPUT_OPTION = "-o";
std::string ENCODE_OPTION = "-e";
std::string DECODE_OPTION = "-d";

// Główna funkcja programu
// Przetwarza i weryfikuje opcje wywołania programu.
// W zależności od wybranej opcji wywołuje odpowiednią klasę do kodowania lub dekodowania.

int main(int argc, char** argv) {
    if (argc == 1) {
        std::cout << "Usage: " << argv[0] << " " << ENCODE_OPTION << "<input file> " << OUTPUT_OPTION << " <output file>" << std::endl;
        std::cout << "Usage: " << argv[0] << " " << DECODE_OPTION << "<input file> " << OUTPUT_OPTION << " <output file>" << std::endl;
        return 1;
    }

    bool outputExists = optionExists(argv, argv + argc, OUTPUT_OPTION);
    bool encodeExists = optionExists(argv, argv + argc, ENCODE_OPTION);
    bool decodeExists = optionExists(argv, argv + argc, DECODE_OPTION);
    
    if (!outputExists) {
        std::cout << "Output file not specified" << std::endl;
        return 1;
    }

    if (encodeExists && decodeExists) {
        std::cout << "Cannot encode and decode at the same time" << std::endl;
        return 1;
    }

    if (!encodeExists && !decodeExists) {
        std::cout << "Either encode or decode must be specified" << std::endl;
        return 1;
    }

    std::string outputFilename = getOption(argv, argv + argc, OUTPUT_OPTION);
    std::string inputFilename = encodeExists ? getOption(argv, argv + argc, ENCODE_OPTION) : getOption(argv, argv + argc, DECODE_OPTION);
    std::ifstream inputFile;
    inputFile.open(inputFilename, std::ios::binary);
    if (!inputFile.is_open() || !inputFile.good()) {
        std::cout << "Error opening input file" << std::endl;
        return 1;
    }

    if (encodeExists) {
        std::string toEncode;
        inputFile.seekg(0, std::ios::end);
        toEncode.resize(inputFile.tellg());
        inputFile.seekg(0, std::ios::beg);
        inputFile.read(&toEncode[0], toEncode.size());
        inputFile.close();
        std::ofstream outputFile;
        outputFile.open(outputFilename, std::ios::binary);
        HuffmanEncoder huffmanEnc = HuffmanEncoder(toEncode);
        huffmanEnc.encode(outputFile);
        outputFile.close();
        return 0;
    }

    if (decodeExists) {
        std::ofstream outputFile;
        outputFile.open(outputFilename, std::ios::binary);
        HuffmanDecoder huffmanDec = HuffmanDecoder(inputFile, outputFile);
        huffmanDec.decode();
        inputFile.close();
        outputFile.close();
        return 0;
    }
    return 0;
}
