#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>

struct HuffmanNode {
    char character;
    size_t frequency;
    HuffmanNode *left;
    HuffmanNode *right;
    
    HuffmanNode(char character, size_t frequency) {
        this -> character = character;
        this -> frequency = frequency;
        left = right = nullptr;
    }

    HuffmanNode(char character, size_t frequency, HuffmanNode *left, HuffmanNode *right) {
        this -> character = character;
        this -> frequency = frequency;
        this -> left = left;
        this -> right = right;
    }

    ~HuffmanNode() {
        delete left;
        delete right;
    }
    
    friend std::ostream& operator<<(std::ostream &os, const HuffmanNode &node) {
        os << node.character << ":" << node.frequency;
        return os;
    }

};

struct CompareHuffmanNodes {
    bool operator()(HuffmanNode *left, HuffmanNode *right) {
        return left -> frequency > right -> frequency;
    }
};

std::unordered_map<char, size_t> buildFrequencyMap(std::string text) {
    std::unordered_map<char, size_t> frequencyMap;
    for (char character : text) {
        frequencyMap[character]++;
    }
    return frequencyMap;
}

HuffmanNode *buildTree(std::unordered_map<char, size_t> frequencyMap) {
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareHuffmanNodes> priorityQueue;

    for (auto pair : frequencyMap) {
        priorityQueue.push(new HuffmanNode(pair.first, pair.second));
    }

    std::cout << "done adding" << std::endl;

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

std::unordered_map<char, std::string> generateCodes(HuffmanNode *root, std::string code, std::unordered_map<char, std::string>& codes) {
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

void printCodes(std::unordered_map<char, std::string> codes) {
    for (auto pair : codes) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }
}

int main() {
    std::string test = "zzzzzxxxxyyya";
    std::cout << "initializing frequency map..." << std::endl; 
    std::unordered_map<char, size_t> freq = buildFrequencyMap(test);
    
    for (auto pair : freq) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }

    std::cout << "building tree..." << std::endl;
    HuffmanNode *huffmanRoot = buildTree(freq);

    std::cout << "generating codes..." << std::endl;
    std::unordered_map<char, std::string> codes;
    generateCodes(huffmanRoot, "", codes);

    std::cout << "printing codes..." << std::endl;
    printCodes(codes);

    return 0;
}