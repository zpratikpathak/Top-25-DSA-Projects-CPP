#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    std::vector<int> docIDs;
};

class SearchIndexer {
    TrieNode* root;

public:
    SearchIndexer() { root = new TrieNode(); }

    void insertWord(std::string word, int docID) {
        TrieNode* curr = root;
        for (char c : word) {
            if (!curr->children.count(c)) curr->children[c] = new TrieNode();
            curr = curr->children[c];
        }
        curr->docIDs.push_back(docID);
    }

    void search(std::string word) {
        TrieNode* curr = root;
        for (char c : word) {
            if (!curr->children.count(c)) {
                std::cout << "Word '" << word << "' not found.\n";
                return;
            }
            curr = curr->children[c];
        }
        std::cout << "Word '" << word << "' found in documents: ";
        for (int id : curr->docIDs) std::cout << id << " ";
        std::cout << "\n";
    }
};

int main() {
    SearchIndexer indexer;
    indexer.insertWord("coding", 1);
    indexer.insertWord("cpp", 1);
    indexer.insertWord("coding", 2);
    indexer.insertWord("dsa", 2);

    indexer.search("coding");
    indexer.search("cpp");
    indexer.search("python");
    return 0;
}
