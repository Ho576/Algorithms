#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <bitset>

using namespace std;

struct Node {
    char data;
    int freq;
    Node* left;
    Node* right;

    Node(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

unordered_map<char, string> huffmanCodes;

void generateCodes(Node* root, string code) {
    if (root->left == nullptr && root->right == nullptr) {
        huffmanCodes[root->data] = code;
        return;
    }

    generateCodes(root->left, code + "0");
    generateCodes(root->right, code + "1");
}

Node* buildHuffmanTree(const unordered_map<char, int>& freq) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (const auto& pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* merged = new Node('$', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }

    return pq.top();
}

string encodeParagraph(const string& paragraph) {
    string encodedBits = "";
    for (char c : paragraph) {
        encodedBits += huffmanCodes[c];
    }
    return encodedBits;
}

string decodeBits(const string& encodedBits, Node* root) {
    string decodedText = "";
    Node* current = root;
    for (char bit : encodedBits) {
        if (bit == '0') {
            current = current->left;
        }
        else {
            current = current->right;
        }

        if (current->left == nullptr && current->right == nullptr) {
            decodedText += current->data;
            current = root;
        }
    }
    return decodedText;
}

int main() {
    string paragraph;
    cout << "Enter a paragraph: ";
    getline(cin, paragraph);

    unordered_map<char, int> freq;
    for (char c : paragraph) {
        freq[c]++;
    }

    Node* huffmanTree = buildHuffmanTree(freq);
    generateCodes(huffmanTree, "");

    cout << "\nHuffman Codes:" << endl;
    for (const auto& pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << endl;
    }

    string encodedParagraph = encodeParagraph(paragraph);
    cout << "\nEncoded paragraph: " << encodedParagraph << endl;

    cout << "Total bits needed: " << encodedParagraph.size() << endl;

    string binarySequence;
    cout << "\nEnter a sequence of binary code: ";
    cin >> binarySequence;

    string decodedText = decodeBits(binarySequence, huffmanTree);
    cout << "Decoded text: " << decodedText << endl;

    delete huffmanTree;

}


//#include <iostream>
//#include <string>
//#include <queue>
//
//using namespace std;
//
//// Node structure for Huffman tree
//struct Node {
//    char data;
//    int freq;
//    Node* left, * right;
//
//    Node(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
//};
//
//// Function to generate Huffman tree and return the root node
//Node* buildHuffmanTree(const string& text) {
//    int frequencies[256] = { 0 }; // Assuming ASCII characters
//
//    // Count occurrences of each character
//    for (char c : text) {
//        frequencies[c]++;
//    }
//
//    auto compare = [](Node* a, Node* b) { return a->freq > b->freq; };
//    priority_queue<Node*, vector<Node*>, decltype(compare)> pq(compare);
//
//    // Create a leaf node for each character and add it to the priority queue
//    for (int i = 0; i < 256; ++i) {
//        if (frequencies[i] > 0) {
//            pq.push(new Node(i, frequencies[i]));
//        }
//    }
//
//    // Construct Huffman tree
//    while (pq.size() > 1) {
//        Node* left = pq.top();
//        pq.pop();
//
//        Node* right = pq.top();
//        pq.pop();
//
//        Node* parent = new Node('$', left->freq + right->freq); // Internal node with special character
//        parent->left = left;
//        parent->right = right;
//
//        pq.push(parent);
//    }
//
//    return pq.top();
//}
//
//// Recursive function to generate Huffman codes for each character
//void generateHuffmanCodes(Node* root, string code, string huffmanCodes[]) {
//    if (root == nullptr) return;
//
//    if (root->data != '$') {
//        huffmanCodes[root->data] = code;
//    }
//
//    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
//    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
//}
//
//int main() {
//    string paragraph;
//    cout << "Enter the text paragraph: ";
//    getline(cin, paragraph);
//
//    // Build Huffman tree
//    Node* root = buildHuffmanTree(paragraph);
//
//    // Generate Huffman codes
//    string huffmanCodes[256];
//    generateHuffmanCodes(root, "", huffmanCodes);
//
//    // Encode the paragraph
//    string encodedParagraph;
//    for (char c : paragraph) {
//        encodedParagraph += huffmanCodes[c];
//    }
//
//    cout << "Encoded paragraph: " << encodedParagraph << endl;
//
//    return 0;
//}

