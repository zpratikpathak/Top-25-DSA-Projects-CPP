#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

/**
 * Advanced Autocomplete System
 * Features:
 * - Prefix-based retrieval using Trie
 * - Search suggestion ranking based on frequency/popularity
 * - Space-efficient node management using unordered_map
 * - Interactive-style suggestion feedback
 */

struct TrieNode {
    std::unordered_map<char, std::shared_ptr<TrieNode>> children;
    bool isEndOfWord = false;
    int weight = 0; // Frequency of search/selection
};

class AutocompleteEngine {
private:
    std::shared_ptr<TrieNode> root;

    void dfs(std::shared_ptr<TrieNode> node, std::string current, std::vector<std::pair<int, std::string>>& suggestions) {
        if (node->isEndOfWord) suggestions.push_back({node->weight, current});
        
        for (auto const& [c, child] : node->children) {
            dfs(child, current + c, suggestions);
        }
    }

public:
    AutocompleteEngine() : root(std::make_shared<TrieNode>()) {}

    void insert(const std::string& word, int weight = 1) {
        auto curr = root;
        for (char c : word) {
            if (!curr->children.count(c)) curr->children[c] = std::make_shared<TrieNode>();
            curr = curr->children[c];
        }
        curr->isEndOfWord = true;
        curr->weight += weight;
    }

    void suggest(const std::string& prefix) {
        auto curr = root;
        for (char c : prefix) {
            if (!curr->children.count(c)) {
                std::cout << "[SYSTEM] No suggestions found for: " << prefix << std::endl;
                return;
            }
            curr = curr->children[c];
        }

        std::vector<std::pair<int, std::string>> results;
        dfs(curr, prefix, results);

        // Sort by weight (Popularity)
        std::sort(results.rbegin(), results.rend());

        std::cout << "\n--- SUGGESTIONS FOR: " << prefix << " ---" << std::endl;
        int count = 0;
        for (auto const& [w, s] : results) {
            std::cout << " > " << s << " (Popularity: " << w << ")" << std::endl;
            if (++count >= 5) break; // Limit suggestions
        }
        std::cout << "------------------------------\n" << std::endl;
    }
};

int main() {
    AutocompleteEngine engine;

    // Build data set
    engine.insert("apple", 50);
    engine.insert("application", 120);
    engine.insert("app store", 80);
    engine.insert("apply", 30);
    engine.insert("banana", 100);
    engine.insert("band", 40);
    engine.insert("bandwidth", 20);

    engine.suggest("app");
    engine.suggest("ban");
    engine.suggest("xyz");

    return 0;
}
