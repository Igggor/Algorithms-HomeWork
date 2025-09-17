#include <string>
#include <queue>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char character, int frequency) : ch(character), freq(frequency), left(nullptr), right(nullptr) {}
    Node(int frequency) : ch('\0'), freq(frequency), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq;
    }
};

Node* buildHuffmanTree(const string& text) {
    unordered_map<char, int> freq;
    for (char ch : text) 
        freq[ch]++;
    
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto pair : freq)
        pq.push(new Node(pair.first, pair.second));


    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* newNode = new Node(left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    return pq.top();
}

void generateCodes(Node* root, string code, unordered_map<char, string>& huffmanCode) {
    if (root == nullptr) return;

    if (root->left == nullptr && root->right == nullptr) {
        huffmanCode[root->ch] = code;
        return;
    }

    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

string encode(const string& text, const unordered_map<char, string>& huffmanCode) {
    string encodedText = "";
    for (char ch : text)
        encodedText += huffmanCode.at(ch);
    
    return encodedText;
}
