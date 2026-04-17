#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <set>

/**
 * Advanced Search Engine Indexer
 * Features:
 * - Inverted Index implementation using Trie and Hash Maps
 * - Document frequency (DF) tracking for future TF-IDF support
 * - Dynamic document addition and complex word querying
 * - Case-insensitive indexing and search
 */

struct Posting {
    int docID;
    int frequency;
    bool operator<(const Posting& other) const { return docID < other.docID; }
};

struct TrieNode {
    std::unordered_map<char, std::shared_ptr<TrieNode>> children;
    std::set<Posting> postings;
    int totalFrequency = 0;
};

class SearchIndexer {
private:
    std::shared_ptr<TrieNode> root;
    int totalDocs = 0;

    std::string clean(std::string s) {
        std::string res = "";
        for (char c : s) if (std::isalnum(c)) res += std::tolower(c);
        return res;
    }

public:
    SearchIndexer() : root(std::make_shared<TrieNode>()) {}

    void indexDocument(int id, const std::string& content) {
        totalDocs++;
        std::string word;
        std::vector<std::string> words;
        size_t start = 0, end = 0;
        
        while ((end = content.find(' ', start)) != std::string::npos) {
            words.push_back(clean(content.substr(start, end - start)));
            start = end + 1;
        }
        words.push_back(clean(content.substr(start)));

        for (const auto& w : words) {
            if (w.empty()) continue;
            auto curr = root;
            for (char c : w) {
                if (!curr->children.count(c)) curr->children[c] = std::make_shared<TrieNode>();
                curr = curr->children[c];
            }
            
            // Update postings
            auto it = std::find_if(curr->postings.begin(), curr->postings.end(), [id](const Posting& p) { return p.docID == id; });
            if (it != curr->postings.end()) {
                Posting p = *it;
                curr->postings.erase(it);
                p.frequency++;
                curr->postings.insert(p);
            } else {
                curr->postings.insert({id, 1});
            }
            curr->totalFrequency++;
        }
    }

    void query(const std::string& word) {
        std::string w = clean(word);
        auto curr = root;
        for (char c : w) {
            if (!curr->children.count(c)) {
                std::cout << "[SEARCH] '" << word << "' not found." << std::endl;
                return;
            }
            curr = curr->children[c];
        }

        std::cout << "\n--- SEARCH RESULTS FOR: " << word << " ---" << std::endl;
        std::cout << "Total Occurrences: " << curr->totalFrequency << std::endl;
        for (const auto& p : curr->postings) {
            std::cout << "Document #" << p.docID << " (Frequency: " << p.frequency << ")" << std::endl;
        }
        std::cout << "-----------------------------------\n" << std::endl;
    }
};

int main() {
    SearchIndexer engine;

    engine.indexDocument(1, "Data Structures and Algorithms are the foundation of computer science.");
    engine.indexDocument(2, "C++ is a high-performance programming language used in systems and DSA.");
    engine.indexDocument(3, "Algorithms can be complex, but data structures make them efficient.");

    engine.query("Algorithms");
    engine.query("DSA");
    engine.query("performance");
    engine.query("python");

    return 0;
}
