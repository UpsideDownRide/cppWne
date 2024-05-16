
#include "huffmanEncoder.h"

HuffmanEncoder::HuffmanEncoder(std::string toEncode) {
    this -> toEncode = toEncode;
    std::cout << "initializing frequency map..." << std::endl; 
    buildFrequencyMap(toEncode);
    std::cout << "building tree..." << std::endl;
    this->root = buildTree(frequencyMap);
    std::cout << "generating codes..." << std::endl;
    generateCodes(root);
    std::cout << "printing codes..." << std::endl;
    printCodes(codes);
}

void HuffmanEncoder::buildFrequencyMap(std::string text) {
    for (char character : text) {
        this -> frequencyMap[character]++;
    }
    return;
}

HuffmanNode *HuffmanEncoder::buildTree(std::unordered_map<char, size_t> frequencyMap) {
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

void HuffmanEncoder::generateCodes(HuffmanNode *current) {
    if (current == nullptr) {
        return;
    }
    if (root -> left != nullptr) {
        generateCodes(root -> left, 0);
    }
    if (root -> right != nullptr) {
        generateCodes(root -> right, 1);
    }
} 

void HuffmanEncoder::generateCodes(HuffmanNode *current, uint8_t code) {
    if (current == nullptr) {
        return;
    }
    
    if (current -> character != '\0') {
        uint8_t bitlength = std::floor(std::log2(code)) + 1;
        CodeWithLength codeWithLength = {code, bitlength};
        codes[current -> character] = codeWithLength;;
        return;
    }

    if (current -> left != nullptr) {
        generateCodes(current -> left, code << 1);
    }

    if (current -> right != nullptr) {
        generateCodes(current -> right, (code << 1) | 1);
    }
    return;
}

void HuffmanEncoder::encode(std::ostream &output) {
    return encode(this -> toEncode, output);
}

void HuffmanEncoder::printCodes(std::unordered_map<char, CodeWithLength> codes) {
    for (auto pair : codes) {
        auto bs = std::bitset<8>(pair.second.code);
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

void HuffmanEncoder::encode(const std::string &input, std::ostream &output) {
    uint8_t code;
    uint8_t bitlength;
    BitWriter bitWriter(output);
    for (auto character : input) {
        std::cout << "encoding " << character << std::endl;
        code = codes[character].code;
        bitlength = codes[character].bitlength;
        if (code == 0) {
            bitWriter.writeBit(0);
            continue;
        }
        code <<= (8 - bitlength);
        for (uint8_t i = 0; i < bitlength; i++) {
            bool bit = (code >> (7 - i)) & 1;
            bitWriter.writeBit(bit);
        }
    }
    bitWriter.flush();
    return;
}

void HuffmanEncoder::decode(std::istream &input, std::ostream &output) {
    HuffmanDecoder huffmanDec = HuffmanDecoder(this->root);
    huffmanDec.decode(input, output);
}

void BitWriter::writeBit(bool bit) {
    buffer |= (bit << (7 - index));
    if (++index == 8) {
        output << buffer;
        buffer = 0;
        index = 0;
    }
}
void BitWriter::flush() {
    if (index > 0) {
        output << buffer;
    }
}
