#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <iomanip>

using namespace std;

// ================= Colors =================
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

// ================= Node =================
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// Min-heap comparison
struct cmp {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// ================= Free Tree =================
void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// ================= Build Huffman Tree =================
Node* buildHuffmanTree(unordered_map<char, int>& freq) {
    priority_queue<Node*, vector<Node*>, cmp> pq;
    for (auto& p : freq)
        pq.push(new Node(p.first, p.second));

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* parent = new Node('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }
    return pq.top();
}

// ================= Generate Huffman Codes =================
void generateCodes(Node* root, string code, unordered_map<char, string>& huffCodes) {
    if (!root) return;
    if (!root->left && !root->right) {
        huffCodes[root->ch] = code;
        return;
    }
    generateCodes(root->left, code + "0", huffCodes);
    generateCodes(root->right, code + "1", huffCodes);
}

// ================= Encode / Decode =================
string encodeText(const string& text, unordered_map<char, string>& huffCodes) {
    string encoded = "";
    for (char c : text) encoded += huffCodes[c];
    return encoded;
}

string decodeText(const string& encoded, Node* root) {
    string decoded = "";
    Node* curr = root;
    for (char bit : encoded) {
        curr = (bit == '0') ? curr->left : curr->right;
        if (!curr->left && !curr->right) {
            decoded += curr->ch;
            curr = root;
        }
    }
    return decoded;
}

// ================= Save/Load Encoded File =================
void saveEncodedFile(const string& filename, unordered_map<char, int>& freq, const string& encoded) {
    ofstream fout(filename);
    fout << freq.size() << "\n";
    for (auto& p : freq) {
        if (p.first == '\n') fout << "\\n " << p.second << "\n";
        else if (p.first == ' ') fout << "_space_ " << p.second << "\n";
        else fout << p.first << " " << p.second << "\n";
    }
    fout << encoded;
}

void loadEncodedFile(const string& filename, unordered_map<char, int>& freq, string& encoded) {
    ifstream fin(filename);
    int n;
    fin >> n;

    string ch;
    int f;
    for (int i = 0; i < n; i++) {
        fin >> ch >> f;
        if (ch == "\\n") freq['\n'] = f;
        else if (ch == "_space_") freq[' '] = f;
        else freq[ch[0]] = f;
    }

    encoded = "";
    string bits;
    while (fin >> bits) encoded += bits;
}

// ================= Compression Stats =================
void showCompressionStats(const string& text, int compressedBits) {
    int originalBits = text.size() * 8;
    double ratio = 100.0 * (1.0 - (double)compressedBits / originalBits);
    double avgBits = (double)compressedBits / text.size();

    cout << "\n===== Compression Statistics =====\n";
    cout << "Original Size        : " << originalBits / 8 << " bytes\n";
    cout << "Compressed Size      : " << compressedBits / 8 << " bytes\n";
    cout << "Original Bits        : " << originalBits << " bits\n";
    cout << "Compressed Bits      : " << compressedBits << " bits\n";
    cout << "Average Bits/Char    : " << avgBits << "\n";
    cout << "Compression Ratio    : " << ratio << "%\n";
}

// ================= Show Frequency Table =================
void showFrequencyTable(unordered_map<char, int>& freq) {
    cout << YELLOW << "\nCharacter Frequency Table:\n" << RESET;
    cout << "---------------------------\n";
    for (auto& p : freq) {
        cout << YELLOW << left << setw(6);
        if (p.first == '\n') cout << "\\n";
        else if (p.first == ' ') cout << "' '";
        else cout << p.first;
        cout << RESET << " : " << p.second << "\n";
    }
}

// ================= Show Huffman Codes =================
void showHuffmanCodes(unordered_map<char, string>& huffCodes) {
    cout << CYAN << "\nGenerated Huffman Codes:\n" << RESET;
    cout << "------------------------\n";
    for (auto& p : huffCodes) {
        cout << CYAN << left << setw(6);
        if (p.first == '\n') cout << "\\n";
        else if (p.first == ' ') cout << "' '";
        else cout << p.first;
        cout << RESET << " -> " << CYAN << p.second << RESET << "\n";
    }
}

// Function to get node as string
string nodeStr(Node* root) {
    if (!root) return "";
    if (!root->left && !root->right) {
        if (root->ch == '\n') return "\\n(" + to_string(root->freq) + ")";
        else if (root->ch == ' ') return "' '(" + to_string(root->freq) + ")";
        else return string(1, root->ch) + "(" + to_string(root->freq) + ")";
    }
    else {
        return "*(" + to_string(root->freq) + ")";
    }
}

// Recursive function to save tree in box style
void saveBoxTree(Node* root, ofstream& fout, string prefix = "", bool isLeft = true) {
    if (!root) return;

    fout << prefix;
    if (prefix != "") fout << (isLeft ? "/-- " : "\\-- ");

    fout << nodeStr(root) << "\n";

    if (root->left || root->right) {
        string childPrefix = prefix + (isLeft ? "|   " : "    ");
        saveBoxTree(root->left, fout, childPrefix, true);
        saveBoxTree(root->right, fout, childPrefix, false);
    }
}


// ================= Main Program =================
int main() {
    unordered_map<char, int> lastFreq;
    unordered_map<char, string> lastCodes;

    while (true) {
        cout << "\n========================================\n";
        cout << "         HUFFMAN COMPRESSION SYSTEM\n";
        cout << "========================================\n";
        cout << "   1) Encode (Compress)\n";
        cout << "   2) Decode (Decompress)\n";
        cout << "   3) Show Last Character Frequency Table\n";
        cout << "   4) Show Last Huffman Codes\n";
        cout << "   5) Exit\n";
        cout << "----------------------------------------\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string filename;
            cout << "Enter input text file name: ";
            getline(cin, filename);

            ifstream fin(filename);
            if (!fin.is_open()) {
                cout << RED << "File not found!\n" << RESET;
                continue;
            }

            string text = "", line;
            while (getline(fin, line)) text += line + "\n";
            fin.close();

            unordered_map<char, int> freq;
            for (char c : text) freq[c]++;
            lastFreq = freq;

            Node* root = buildHuffmanTree(freq);
            unordered_map<char, string> huffCodes;
            generateCodes(root, "", huffCodes);
            lastCodes = huffCodes;

            string encoded = encodeText(text, huffCodes);
            saveEncodedFile("encoded.txt", freq, encoded);

            cout << GREEN << "\nEncoding completed. File saved as 'encoded.txt'\n" << RESET;
            showCompressionStats(text, encoded.size());

            // Save Huffman tree in box style to file
            ofstream treeFile("huffman_tree.txt");
            saveBoxTree(root, treeFile);
            treeFile.close();
            cout << GREEN << endl << "Huffman tree saved as 'huffman_tree.txt'\n" << RESET;

            freeTree(root);
        }

        else if (choice == 2) {
            unordered_map<char, int> freq;
            string encoded;
            loadEncodedFile("encoded.txt", freq, encoded);

            Node* root = buildHuffmanTree(freq);
            string decoded = decodeText(encoded, root);
            ofstream fout("decoded.txt");
            fout << decoded;
            fout.close();
            freeTree(root);

            cout << GREEN << "\nDecoding completed. File saved as 'decoded.txt'\n" << RESET;
        }

        else if (choice == 3) {
            if (lastFreq.empty()) {
                cout << RED << "No data available. Encode a file first.\n" << RESET;
            }
            else {
                showFrequencyTable(lastFreq);
            }
        }

        else if (choice == 4) {
            if (lastCodes.empty()) {
                cout << RED << "No Huffman codes available. Encode a file first.\n" << RESET;
            }
            else {
                showHuffmanCodes(lastCodes);
            }
        }

        else if (choice == 5) {
            cout << "Exiting program...\n";
            break;
        }

        else {
            cout << RED << "Invalid choice! Try again.\n" << RESET;
        }
    }

    return 0;
}
