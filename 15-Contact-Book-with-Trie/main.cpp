#include <iostream>
#include <unordered_map>
#include <string>

struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    std::string phoneNumber;
    bool isEndOfName;

    TrieNode() : phoneNumber(""), isEndOfName(false) {}
};

class ContactBook {
    TrieNode* root;

public:
    ContactBook() { root = new TrieNode(); }

    void addContact(std::string name, std::string phone) {
        TrieNode* curr = root;
        for (char c : name) {
            if (!curr->children.count(c)) curr->children[c] = new TrieNode();
            curr = curr->children[c];
        }
        curr->isEndOfName = true;
        curr->phoneNumber = phone;
    }

    void findContact(std::string name) {
        TrieNode* curr = root;
        for (char c : name) {
            if (!curr->children.count(c)) {
                std::cout << "Contact '" << name << "' not found.\n";
                return;
            }
            curr = curr->children[c];
        }
        if (curr->isEndOfName) {
            std::cout << name << ": " << curr->phoneNumber << "\n";
        } else {
            std::cout << "Contact '" << name << "' not found.\n";
        }
    }
};

int main() {
    ContactBook contacts;
    contacts.addContact("Pratik", "+91 9999999999");
    contacts.addContact("Evil", "+1 8888888888");

    contacts.findContact("Pratik");
    contacts.findContact("Alice");
    return 0;
}
