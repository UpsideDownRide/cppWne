
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
    return length;
}

std::ostream &operator<<(std::ostream &os, const fileHeader &header) {
    os.write(reinterpret_cast<const char*>(&header.encodingLength), sizeof(header.encodingLength));
    return os;
}

void encodeTree(HuffmanNode *current, BitWriter &bitWriter) {
    if (current == nullptr) {
        return;
    }
    if (current -> character == '\0') {
        bitWriter.writeBit(0);
    } else {
        bitWriter.writeBit(1);
        bitWriter.writeChar(current -> character);
    }
    encodeTree(current -> left, bitWriter);
    encodeTree(current -> right, bitWriter);
    return;
}

void HuffmanEncoder::encode(std::ostream &output) {
    std::stringstream buffer;
    uint16_t treeLength;
    BitWriter bitWriter(buffer);
    
    encodeTree(this -> root, bitWriter);
    bitWriter.flush();
    buffer.seekg(0, std::ios::end);
    treeLength = buffer.tellg();
    buffer.seekg(0, std::ios::beg);

    fileHeader header{getEncodingLength()};
    output << header;
    output << buffer.rdbuf();

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

void BitWriter::writeBit(bool bit) {
    buffer |= (bit << (7 - index));
    if (++index == 8) {
        output.write(reinterpret_cast<const char*>(&buffer), sizeof(buffer));
        buffer = 0;
        index = 0;
    }
}

void BitWriter::writeChar(char character) {
    for (int i = 7; i >= 0; i--) {
        BitWriter::writeBit((character >> i) & 1);
    }
}

void BitWriter::flush() {
    if (index > 0) {
        output << buffer;
    }
}