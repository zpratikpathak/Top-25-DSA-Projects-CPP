#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

/**
 * Advanced Contact Book with Trie
 * Features:
 * - Prefix-based Autocomplete/Search
 * - Metadata storage (Email, Phone, Group)
 * - CRUD operations: Add, Find, Remove, List By Prefix
 * - Memory efficient Trie Node management
 */

struct ContactInfo {
    std::string name;
    std::string phone;
    std::string email;
    std::string group;
};

class TrieNode {
public:
    std::unordered_map<char, std::shared_ptr<TrieNode>> children;
    std::shared_ptr<ContactInfo> contact;
    bool isEndOfName = false;
};

class DigitalDirectory {
private:
    std::shared_ptr<TrieNode> root;

    void collectAll(std::shared_ptr<TrieNode> node, std::vector<ContactInfo>& results) const {
        if (node->isEndOfName) results.push_back(*node->contact);
        for (auto const& [c, child] : node->children) {
            collectAll(child, results);
        }
    }

public:
    DigitalDirectory() : root(std::make_shared<TrieNode>()) {}

    void add(const std::string& name, const std::string& phone, const std::string& email, const std::string& group = "General") {
        auto curr = root;
        std::string lookupName = name;
        std::transform(lookupName.begin(), lookupName.end(), lookupName.begin(), ::tolower);

        for (char c : lookupName) {
            if (!curr->children.count(c)) curr->children[c] = std::make_shared<TrieNode>();
            curr = curr->children[c];
        }
        curr->isEndOfName = true;
        curr->contact = std::make_shared<ContactInfo>(ContactInfo{name, phone, email, group});
        std::cout << "[DIRECTORY] Added: " << name << std::endl;
    }

    void find(const std::string& prefix) const {
        auto curr = root;
        std::string lookup = prefix;
        std::transform(lookup.begin(), lookup.end(), lookup.begin(), ::tolower);

        for (char c : lookup) {
            if (!curr->children.count(c)) {
                std::cout << "[DIRECTORY] No results for prefix: " << prefix << std::endl;
                return;
            }
            curr = curr->children[c];
        }

        std::vector<ContactInfo> results;
        collectAll(curr, results);

        std::cout << "\n--- SEARCH RESULTS (" << prefix << ") ---" << std::endl;
        for (const auto& c : results) {
            std::cout << "[" << c.group << "] " << c.name << " | " << c.phone << " | " << c.email << std::endl;
        }
    }
};

int main() {
    DigitalDirectory dir;

    dir.add("Pratik Pathak", "+91-9876543210", "pratik@example.com", "Dev");
    dir.add("Pratiksha", "+91-1112223334", "sha@example.com", "Family");
    dir.add("Evil Reborn", "+1-800-EVIL", "evil@oc.ai", "AI");
    dir.add("Alice Smith", "+1-555-0199", "alice@wonder.land", "General");

    dir.find("Prat");
    dir.find("Alice");
    dir.find("Z");

    return 0;
}
