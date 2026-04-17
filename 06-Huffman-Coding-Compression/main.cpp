#include <iostream>
#include <vector>
#include <queue>
#include <map>

struct Node {
    char data;
    int freq;
    Node *left, *right;
    Node(char d, int f) : data(d), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* l, Node* r) { return l->freq > r->freq; }
};

void printCodes(Node* root, std::string str) {
    if (!root) return;
    if (root->data != '$') std::cout << root->data << ": " << str << "\n";
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

void HuffmanCodes(char data[], int freq[], int size) {
    std::priority_queue<Node*, std::vector<Node*>, Compare> minHeap;
    for (int i = 0; i < size; ++i) minHeap.push(new Node(data[i], freq[i]));

    while (minHeap.size() != 1) {
        Node *left = minHeap.top(); minHeap.pop();
        Node *right = minHeap.top(); minHeap.pop();
        Node *top = new Node('$', left->freq + right->freq);
        top->left = left; top->right = right;
        minHeap.push(top);
    }
    printCodes(minHeap.top(), "");
}

int main() {
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };
    HuffmanCodes(arr, freq, 6);
    return 0;
}
