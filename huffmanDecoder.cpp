#include "huffmanDecoder.h"

void HuffmanDecoder::decode(std::istream &input, std::ostream &output) {
    HuffmanNode *current = this->root;
    std::cout << "decoding..." << std::endl;
    for (std::istreambuf_iterator<char> iter(input), end; iter != end; ++iter) {
        bool bit;
        for (int i = 7; i >= 0; i--) {
            bit = (*iter >> i) & 1;
            if (bit) {
                current = (current->right);
            } else {
                current = (current->left);
            }
            if (current -> left == nullptr && current -> right == nullptr) {
                output << current -> character;
                current = root;
            }
            
        }
    }
    return;
}