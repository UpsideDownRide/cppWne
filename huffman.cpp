
#include "huffman.h"

Huffman::Huffman(std::string toEncode) {
    this -> toEncode = toEncode;
    frequencyMap = buildFrequencyMap(toEncode);
    root = buildTree(frequencyMap);
    codes = generateCodes(root, "", codes);
}

std::unordered_map<char, size_t> Huffman::buildFrequencyMap(std::string text) {
    std::unordered_map<char, size_t> frequencyMap;
    for (char character : text) {
        frequencyMap[character]++;
    }
    return frequencyMap;
}

HuffmanNode *Huffman::buildTree(std::unordered_map<char, size_t> frequencyMap) {
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareHuffmanNodes> priorityQueue;

    for (auto pair : frequencyMap) {
        priorityQueue.push(new HuffmanNode(pair.first, pair.second));
    }

    while (priorityQueue.size() > 1) {
        HuffmanNode *left = priorityQueue.top();
        priorityQueue.pop();

        HuffmanNode *right = priorityQueue.top();
        priorityQueue.pop();

        size_t sum = left -> frequency + right -> frequency;
        HuffmanNode *nodeToAdd = new HuffmanNode('\0', sum, left, right);
        std::cout << "adding branch " << *nodeToAdd << std::endl;
        std::cout << "with leaves " << *left << " and " << *right << std::endl;
        priorityQueue.push(nodeToAdd);
    }

    return priorityQueue.top();
}

std::unordered_map<char, std::string> Huffman::generateCodes(HuffmanNode *root, std::string code, std::unordered_map<char, std::string>& codes) {
    if (root == nullptr) {
        return codes;
    }

    if (root -> character != '\0') {
        codes[root -> character] = code;
    }

    generateCodes(root -> left, code + "0", codes);
    generateCodes(root -> right, code + "1", codes);
    return codes;
}

void Huffman::printCodes(std::unordered_map<char, std::string> codes) {
    for (auto pair : codes) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }
}