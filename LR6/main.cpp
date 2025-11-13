#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <Windows.h>

using namespace std;

struct HuffmanNode {
    char character;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char ch, int freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
    HuffmanNode(int freq, HuffmanNode* l, HuffmanNode* r) : character('\0'), frequency(freq), left(l), right(r) {}
};

struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

class HuffmanCoding {
private:
    HuffmanNode* root;
    unordered_map<char, string> huffmanCodes;
    unordered_map<char, int> frequencyTable;

    void buildCodes(HuffmanNode* node, string code) {
        if (node == nullptr) return;

        if (node->left == nullptr && node->right == nullptr) {
            huffmanCodes[node->character] = code;
            return;
        }

        buildCodes(node->left, code + "0");
        buildCodes(node->right, code + "1");
    }

    void deleteTree(HuffmanNode* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    HuffmanCoding() : root(nullptr) {}

    ~HuffmanCoding() {
        deleteTree(root);
    }

    void buildFrequencyTable(const string& text) {
        frequencyTable.clear();
        for (char ch : text) {
            frequencyTable[ch]++;
        }
    }

    void buildHuffmanTree() {
        huffmanCodes.clear();

        priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

        for (auto& pair : frequencyTable) {
            pq.push(new HuffmanNode(pair.first, pair.second));
        }

        while (pq.size() > 1) {
            HuffmanNode* left = pq.top(); pq.pop();
            HuffmanNode* right = pq.top(); pq.pop();

            HuffmanNode* parent = new HuffmanNode(left->frequency + right->frequency, left, right);
            pq.push(parent);
        }

        root = pq.top();

        buildCodes(root, "");
    }

    string encode(const string& text) {
        string encodedText = "";
        for (char ch : text) {
            encodedText += huffmanCodes[ch];
        }
        return encodedText;
    }

    void printFrequencyTable() {
        cout << "Таблица встречаемости символов" << endl;
        cout << setw(20) << "Символ" << setw(25) << "Количество" << setw(20) << "Процент" << endl;
        cout << string(40, '-') << endl;

        int totalChars = 0;
        for (auto& pair : frequencyTable) {
            totalChars += pair.second;
        }

        vector<pair<char, int>> sortedFreq(frequencyTable.begin(), frequencyTable.end());
        sort(sortedFreq.begin(), sortedFreq.end(),
             [](const pair<char, int>& a, const pair<char, int>& b) {
                 return a.second > b.second;
             });

        for (auto& pair : sortedFreq) {
            double percentage = (static_cast<double>(pair.second) / totalChars) * 100;
            if (pair.first == ' ') {
                cout << setw(10) << " " << setw(20) << pair.second << setw(25) << fixed << setprecision(2) << percentage << endl;
            } else if (pair.first == '\n') {
                cout << setw(10) << "\n" << setw(15) << pair.second << setw(15) << fixed << setprecision(2) << percentage << endl;
            } else {
                cout << setw(10) << pair.first << setw(15) << pair.second << setw(15) << fixed << setprecision(2) << percentage << endl;
            }
        }
    }

    void printHuffmanCodes() {
        cout << "Таблица кодов Хаффмана" << endl;
        cout << setw(15) << "Символ" << setw(25) << "Кодовая последовательность" << setw(25) << "Длина кода" << endl;
        cout << string(45, '-') << endl;

        vector<pair<char, string>> sortedCodes(huffmanCodes.begin(), huffmanCodes.end());
        sort(sortedCodes.begin(), sortedCodes.end(),
             [](const pair<char, string>& a, const pair<char, string>& b) {
                 return a.second.length() < b.second.length();
             });

        for (auto& pair : sortedCodes) {
            if (pair.first == ' ') {
                cout << setw(10) << " " << setw(20) << pair.second << setw(15) << pair.second.length() << endl;
            } else if (pair.first == '\n') {
                cout << setw(10) << "\n" << setw(20) << pair.second << setw(15) << pair.second.length() << endl;
            } else {
                cout << setw(10) << pair.first << setw(20) << pair.second << setw(15) << pair.second.length() << endl;
            }
        }
    }

    void printEncodedText(const string& encodedText, const string& originalText) {
        cout << "Результаты кодирования" << endl;
        cout << "Исходный текст: " << originalText << endl;
        cout << "Длина исходного текста: " << originalText.length() << " символов" << endl;
        cout << "Длина исходного текста в битах (ASCII): " << originalText.length() * 8 << " бит" << endl;

        cout << "\nЗакодированная последовательность:" << endl;
        cout << encodedText << endl;
        cout << "Длина закодированной последовательности: " << encodedText.length() << " бит" << endl;

        double compressionRatio = (1.0 - static_cast<double>(encodedText.length()) / (originalText.length() * 8)) * 100;
        cout << "Коэффициент сжатия: " << fixed << setprecision(2) << compressionRatio << "%" << endl;
    }

    const unordered_map<char, string>& getCodes() const {
        return huffmanCodes;
    }

    const unordered_map<char, int>& getFrequencyTable() const {
        return frequencyTable;
    }
};

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    HuffmanCoding huffman;
    string text;

    cout << "Введите текст для кодирования: ";

    getline(cin, text);

    if (text == "") {
        return 0;
    }

    huffman.buildFrequencyTable(text);

    huffman.buildHuffmanTree();

    string encodedText = huffman.encode(text);

    huffman.printFrequencyTable();
    huffman.printHuffmanCodes();
    huffman.printEncodedText(encodedText, text);

    return 0;
}