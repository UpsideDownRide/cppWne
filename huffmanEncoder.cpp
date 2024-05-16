
#include "huffmanEncoder.h"

HuffmanEncoder::HuffmanEncoder(std::string toEncode) {
    this -> toEncode = toEncode;
    buildFrequencyMap(toEncode);
    this->root = buildTree(frequencyMap);
    generateCodes(root, "");
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
        priorityQueue.push(nodeToAdd);
    }

    return priorityQueue.top();
}

void HuffmanEncoder::generateCodes(HuffmanNode *current, std::string code) {
    if (current == nullptr) {
        return;
    }
    
    if (current -> character != '\0') {
        codes[current -> character] = code;
        return;
    }

    if (current -> left != nullptr) {
        generateCodes(current -> left, code + "0");
    }

    if (current -> right != nullptr) {
        generateCodes(current -> right, code + "1");
    }
    return;
}

size_t HuffmanEncoder::getEncodingLength() {
    size_t length = 0;
    for (auto pair : this->frequencyMap){
        length += this->codes[pair.first].length() * pair.second;
    }
    std::cout << "computed length: " << length << std::endl;
    return length;
}

std::ostream &operator<<(std::ostream &os, const fileHeader &header) {
    os.write(reinterpret_cast<const char*>(&header.treeLength), sizeof(header.treeLength));
    os.write(reinterpret_cast<const char*>(&header.encodingLength), sizeof(header.encodingLength));
    return os;
}

void HuffmanEncoder::encode(std::ostream &output) {
    fileHeader header{0, getEncodingLength()};
    output << header;
    _encode(this -> toEncode, output);
    return;
}

void HuffmanEncoder::printCodes(std::unordered_map<char, std::string> codes) {
    for (auto pair : codes) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }
}

void HuffmanEncoder::_encode(const std::string &input, std::ostream &output) {
    std::string code;
    BitWriter bitWriter(output);
    size_t length = 0;
    for (auto character : input) {
        code = codes[character];
        for (auto ch : code) {
            bitWriter.writeBit(ch == '1');
        }
        length += code.length();
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
