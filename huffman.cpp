
#include "huffman.h"
Huffman::Huffman(std::string toEncode) {
    this -> toEncode = toEncode;
    std::cout << "initializing frequency map..." << std::endl; 
    frequencyMap = buildFrequencyMap(toEncode);
    for (auto pair : frequencyMap) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }

    std::cout << "building tree..." << std::endl;
    this->root = buildTree(frequencyMap);
    std::cout << "generating codes..." << std::endl;
    generateCodes(root, 0);
    std::cout << "printing codes..." << std::endl;
    printCodes(codes);
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
        HuffmanNode *nodeToAdd = new HuffmanNode(0, sum, left, right);
        std::cout << "adding branch " << *nodeToAdd << std::endl;
        std::cout << "with leaves " << *left << " and " << *right << std::endl;
        priorityQueue.push(nodeToAdd);
    }

    return priorityQueue.top();
}

void Huffman::generateCodes(HuffmanNode *root, uint8_t code) {
    if (root -> left == nullptr && root -> right == nullptr) {
        codes[root -> code] = code;
        return;
    }

    if (root -> left != nullptr) {
        generateCodes(root -> left, code << 1);
    }

    if (root -> right != nullptr) {
        generateCodes(root -> right, (code << 1) | 1);
    }
}

std::ostream& Huffman::encode(const std::string &input, std::ostream &output) {
    uint8_t buffer = 0;
    uint8_t index = 0;
    for (auto character : input) {
        uint8_t code = codes[character];    
        while (code > 0) {
            buffer <<= 1;
            if (code & 1) {
                buffer |= 1;
            }
            code >>= 1;
            if (++index == 8) {
                output << buffer;
                buffer = 0;
                index = 0;
            }
        }
    }
    if (index > 0) {
        buffer = buffer << (8 - index);
        output << buffer;
    }
    return output;
}

std::ostream &Huffman::decode(const std::string &input, std::ostream &output) {
    HuffmanNode *current = root;
    auto reverseCodes = std::unordered_map<uint8_t, char>();
    std::cout << "decoding..." << std::endl;
    for (auto pair : codes) {
        reverseCodes[pair.second] = pair.first;
    }
    for (auto byte : input) {
        for (int i = 7; i >= 0; i--) {
            if ((current -> left) == nullptr) {
                std::cout << reverseCodes[current -> code];
                output << reverseCodes[current -> code];
                current = root;
            }
            bool bit = (byte >> i) & 1;
            if (bit) {
                current = (current->right);
            } else {
                current = (current->left);
            }

        }
    }
    return output;
}

std::ostream &Huffman::encode(std::ostream &output) {
    std::cout << "encoding..." << std::endl;
    return encode(this -> toEncode, output);
}

void Huffman::printCodes(std::unordered_map<char, uint8_t> codes) {
    for (auto pair : codes) {
        auto bs = std::bitset<8>(pair.second);
        std::string binary;
        if(bs != 0) {
            binary = bs.to_string();
            binary.erase(0, binary.find_first_not_of('0'));
        } else {
            binary = "0";
        }
        std::cout << pair.first << " " << binary << std::endl;
    }
}