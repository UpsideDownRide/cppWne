// Klasa HuffmanDecoder
// Klasa odpowiedzialna za dekodowanie pliku zakodowanego przy pomocy klasy HuffmanEncoder.
// W polach klasy przechowywane są wskaźniki na korzeń drzewa Huffmana oraz aktualny węzeł.
// W polach przechowywane są referencje do strumieni wejściowego i wyjściowego.


#include "huffmanDecoder.h"

// Metoda pomocnicza przetwarzająca nagłówek pliku.
inline fileHeader processHeader(std::istream &input) {
    fileHeader header;
    input.read(reinterpret_cast<char*>(&header.encodingLength), sizeof(header.encodingLength));
    return header;
}

// Metoda pomocnicza generująca drzewo Huffmana na podstawie binarnej reprezentacji drzewa.
// Jeżeli odczytany bit jest równy 1, odczytywany jest znak po nim następujący i tworzony jest liść drzewa.
// W przeciwnym wypadku rekurencyjnie wywoływana jest metoda generująca drzewo dla lewego i prawego poddrzewa.
// Metoda zwraca wskaźnik na korzeń drzewa.

HuffmanNode* generateTree(BitReader &reader) {
    if (reader.readBit()) {
        char character = reader.readChar();
        return new HuffmanNode(character, 0);
    } else {
        HuffmanNode *left = generateTree(reader);
        HuffmanNode *right = generateTree(reader);
        return new HuffmanNode('\0', 0, left, right);
    }
}

// Metoda dekodująca zakodowany plik.
// Metoda kolejno odczytuje nagłówek pliku, generuje drzewo Huffmana, a następnie dekoduje zakodowany tekst.
// W zależności od odczytanego bitu przechodzi do lewego lub prawego dziecka aktualnego węzła.
// Jeżeli aktualny węzeł jest liściem, zapisuje znak w pliku wyjściowym i przechodzi do korzenia drzewa.

void HuffmanDecoder::decode() {
    char* byte = new char[1];
    fileHeader header;
    
    if (input.good()) {
        header = processHeader(input);
    } else {
        std::cout << "Error with the input" << std::endl;
        return;
    }
    
    BitReader reader = BitReader(input);
    root = generateTree(reader);
    current = root;

    size_t processed = 0;
    
    while (!input.eof() && processed <= header.encodingLength) {
        input.read(byte, 1);
        for (int i = 7; i >= 0 && processed <= header.encodingLength; i--, processed++) {
            bool bit = (byte[0] >> i) & 1;
            if (bit) {
                current = (current->right);
            } else {
                current = (current->left);
            }
            if (current -> left == nullptr && current -> right == nullptr) {
                output << current -> character;
                current = this->root;
            }
        }
    }
    return;
}
// Konstruktor klasy BitReader przyjmuje referencję do strumienia wejściowego.
// Wczytuje pierwszy bajt ze strumienia i zapisuje go w buforze.
BitReader::BitReader(std::istream &input) : input(input), buffer(0), index(0) {
    input.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
}

// Metoda readBit odczytuje bit z bufora.
// Kiedy dojdzie do końca bufora, wczytuje kolejny bajt ze strumienia. 
bool BitReader::readBit() {
    bool bit = (buffer >> (7 - index)) & 1;
    if (++index == 8) {
        input.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
        index = 0;
    }
    return bit;
}

// Metoda pomocnicza wczytująca pełen znak z bufora.
char BitReader::readChar() {
    char character = 0;
    for (int i = 7; i >= 0; i--) {
        character |= (readBit() << i);
    }
    return character;
}