// Klasa HuffmanEncoder jest odpowiedzialna za kodowanie tekstu za pomocą algorytmu
// Huffmana. W kolejnych krokach algorytmu tworozne są - mapa częstości występowania
// znaków, drzewo Huffmana oraz kody znaków. Na podstawie kodów przyjęty tekst jest
// kodowany.

#include "huffmanEncoder.h"

// Konstruktor klasy HuffmanEncoder
HuffmanEncoder::HuffmanEncoder(std::string toEncode) {
    this -> toEncode = toEncode;
    buildFrequencyMap(toEncode);
    this->root = buildTree(frequencyMap);
    generateCodes(root, "");
}

// Metoda budująca mapę częstości występowania znaków
void HuffmanEncoder::buildFrequencyMap(std::string text) {
    for (char character : text) {
        this -> frequencyMap[character]++;
    }
    return;
}

// Metoda budująca drzewo Huffmana
// Dla każdej pary znak - częstość tworzony jest węzeł drzewa.
// Następnie węzły są dodawane do kolejki priorytetowej.
// W pętli while pobierane są dwa węzły z kolejki, które są ze sobą łączone w jeden węzeł.
// Węzeł ten jest ponownie dodawany do kolejki.
// Proces jest powtarzany aż w kolejce zostanie jeden węzeł - korzeń drzewa.

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

// Metoda generująca kody znaków
// Metoda rekurencyjnie przechodzi po drzewie Huffmana. I dla każdego węzła rekurencyjnie generuje
// kody znaków - 0 dla lewego dziecka, 1 dla prawego dziecka.
// Kody znaków są zapisywane w mapie kodów.

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

// Metoda pomocnicza zwracająca długość zakodowanego tekstu. 
// Wykorzystywana przy generowaniu nagłówka pliku.

size_t HuffmanEncoder::getEncodingLength() {
    size_t length = 0;
    for (auto pair : this->frequencyMap){
        length += this->codes[pair.first].length() * pair.second;
    }
    return length;
}

// Przeciążony operator << dla klasy fileHeader
// Zapisuje nagłówek pliku.
std::ostream &operator<<(std::ostream &os, const fileHeader &header) {
    os.write(reinterpret_cast<const char*>(&header.encodingLength), sizeof(header.encodingLength));
    return os;
}

// Metoda zapisująca reprezentację drzewa Huffmana w formie binarnej.
// Reprezentacja zapisywana jest w następujący sposób:
// 0 - węzeł wewnętrzny
// 1 - liść
// tuż po każdym liściu zapisywanych jest 8 bitów reprezentujących znak.

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

// Metoda kodująca tekst wejściowy.
// W pierwszym krokuy zapiswana jest reprezentacja drzewa Huffmana w formie binarnej do bufora.
// Następnie zapisywany jest nagłówek pliku z długością zakodowanego tekstu.
// Po nim zapisywana jest reprezentacja drzewa Huffmana z bufora.
// Na końcu zapisywany jest zakodowany tekst.

void HuffmanEncoder::encode(std::ostream &output) {
    std::stringstream buffer;
    BitWriter bitWriter(buffer);
    
    encodeTree(this -> root, bitWriter);
    bitWriter.flush();

    fileHeader header{getEncodingLength()};
    output << header;
    output << buffer.rdbuf();

    _encode(this -> toEncode, output);
    return;
}

// Metoda pomocnicza kodująca tekst wejściowy. Wydzielona dla klarowności kodu.
// Dla każdego znaku z tekstu wejściowego pobierany jest kod znaku z mapy kodów.
// Następnie każdy bit kodu jest zapisywany do strumienia wyjściowego.
// Na końcu opróżniany jest bufor w celu zapewnienia zapisywania bitów w pełnych bajtach.

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

// Klasa pomocnicza BitWriter
// Klasa odpowiedzialna za zapisywanie bitów do strumienia wyjściowego.
// W polach klasy przechowywany jest bufor oraz indeks ostatniego zapisanego bitu.
 
// Metoda writeBit. Zapisuje bit do bufora. Jeżeli bufor jest pełny, zapisuje bufor do strumienia wyjściowego.
// I zeruje bufor oraz indeks.
void BitWriter::writeBit(bool bit) {
    buffer |= (bit << (7 - index));
    if (++index == 8) {
        output.write(reinterpret_cast<const char*>(&buffer), sizeof(buffer));
        buffer = 0;
        index = 0;
    }
}

// Metoda writeChar. Zapisuje znak do strumienia wyjściowego za pomocą metody writeBit.
void BitWriter::writeChar(char character) {
    for (int i = 7; i >= 0; i--) {
        BitWriter::writeBit((character >> i) & 1);
    }
}

// Metoda flush. Zapisuje bufor do strumienia wyjściowego.
void BitWriter::flush() {
    if (index > 0) {
        output << buffer;
    }
}