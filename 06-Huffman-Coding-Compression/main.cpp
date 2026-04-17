#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <memory>
#include <bitset>

/**
 * Advanced Huffman Coding Compression
 * Features:
 * - Optimal code tree construction using Greedy Priority Queue
 * - Support for full string encoding and decoding
 * - Frequency analysis and Compression Ratio metrics
 * - Object-oriented tree representation
 */

class HuffmanNode {
public:
    char character;
    int frequency;
    std::shared_ptr<HuffmanNode> left, right;

    HuffmanNode(char c, int f) : character(c), frequency(f), left(nullptr), right(nullptr) {}
};

struct CompareNodes {
    bool operator()(std::shared_ptr<HuffmanNode> const& l, std::shared_ptr<HuffmanNode> const& r) {
        return l->frequency > r->frequency;
    }
};

class HuffmanEngine {
private:
    std::shared_ptr<HuffmanNode> root;
    std::map<char, std::string> codes;

    void generateCodes(std::shared_ptr<HuffmanNode> node, const std::string& currentCode) {
        if (!node) return;
        if (!node->left && !node->right) codes[node->character] = currentCode;

        generateCodes(node->left, currentCode + "0");
        generateCodes(node->right, currentCode + "1");
    }

public:
    void buildTree(const std::string& text) {
        std::map<char, int> freqMap;
        for (char c : text) freqMap[c]++;

        std::priority_queue<std::shared_ptr<HuffmanNode>, std::vector<std::shared_ptr<HuffmanNode>>, CompareNodes> pq;
        for (auto const& [charVal, freq] : freqMap) {
            pq.push(std::make_shared<HuffmanNode>(charVal, freq));
        }

        while (pq.size() > 1) {
            auto left = pq.top(); pq.pop();
            auto right = pq.top(); pq.pop();
            auto combined = std::make_shared<HuffmanNode>('\0', left->frequency + right->frequency);
            combined->left = left;
            combined->right = right;
            pq.push(combined);
        }

        root = pq.top();
        generateCodes(root, "");
    }

    std::string encode(const std::string& text) {
        std::string encoded = "";
        for (char c : text) encoded += codes[c];
        return encoded;
    }

    std::string decode(const std::string& encodedText) {
        std::string decoded = "";
        auto curr = root;
        for (char bit : encodedText) {
            if (bit == '0') curr = curr->left;
            else curr = curr->right;

            if (!curr->left && !curr->right) {
                decoded += curr->character;
                curr = root;
            }
        }
        return decoded;
    }

    void showAnalytics(const std::string& original, const std::string& encoded) {
        int originalBits = original.length() * 8;
        int encodedBits = encoded.length();
        std::cout << "\n--- HUFFMAN ANALYTICS ---" << std::endl;
        std::cout << "Original Size:  " << originalBits << " bits" << std::endl;
        std::cout << "Compressed Size: " << encodedBits << " bits" << std::endl;
        std::cout << "Saving Ratio:    " << (1.0f - (float)encodedBits / originalBits) * 100 << "%" << std::endl;
        std::cout << "-------------------------\n" << std::endl;
    }
};

int main() {
    std::string source = "The goal of compression is to reduce the data volume without losing information.";
    HuffmanEngine huff;
    
    huff.buildTree(source);
    std::string encoded = huff.encode(source);
    std::string decoded = huff.decode(encoded);

    std::cout << "Original:  " << source << std::endl;
    std::cout << "Encoded:   " << encoded.substr(0, 50) << "..." << std::endl;
    std::cout << "Decoded:   " << decoded << std::endl;

    huff.showAnalytics(source, encoded);

    return 0;
}
