#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
};

class Autocomplete {
    TrieNode* root;

    void collectSuggestions(TrieNode* node, std::string current, std::vector<std::string>& results) {
        if (node->isEndOfWord) results.push_back(current);
        for (auto const& [c, child] : node->children) {
            collectSuggestions(child, current + c, results);
        }
    }

public:
    Autocomplete() { root = new TrieNode(); }

    void insert(std::string word) {
        TrieNode* curr = root;
        for (char c : word) {
            if (!curr->children.count(c)) curr->children[c] = new TrieNode();
            curr = curr->children[c];
        }
        curr->isEndOfWord = true;
    }

    std::vector<std::string> getSuggestions(std::string prefix) {
        TrieNode* curr = root;
        std::vector<std::string> results;
        for (char c : prefix) {
            if (!curr->children.count(c)) return {};
            curr = curr->children[c];
        }
        collectSuggestions(curr, prefix, results);
        return results;
    }
};

int main() {
    Autocomplete ac;
    ac.insert("apple");
    ac.insert("app");
    ac.insert("application");
    ac.insert("banana");

    auto suggestions = ac.getSuggestions("app");
    std::cout << "Suggestions for 'app': ";
    for (auto const& s : suggestions) std::cout << s << " ";
    std::cout << "\n";
    return 0;
}
