#include <iostream>
#include <string>
#include <vector>
#include <map>

class Node {
public:
    std::string name;
    bool isDirectory;
    std::map<std::string, Node*> children;
    
    Node(std::string n, bool dir) : name(n), isDirectory(dir) {}
};

class FileSystem {
    Node* root;
    Node* current;

public:
    FileSystem() {
        root = new Node("/", true);
        current = root;
    }

    void mkdir(std::string name) {
        if (current->children.find(name) == current->children.end()) {
            current->children[name] = new Node(name, true);
            std::cout << "Directory created: " << name << "\n";
        } else {
            std::cout << "Error: Directory exists.\n";
        }
    }

    void ls() {
        std::cout << "Contents of " << current->name << ":\n";
        for (auto const& [name, node] : current->children) {
            std::cout << (node->isDirectory ? "[DIR] " : "[FILE] ") << name << "\n";
        }
    }

    void cd(std::string name) {
        if (name == "..") {
            // Simplification: logic to go back would need parent pointers
            current = root;
            return;
        }
        if (current->children.find(name) != current->children.end() && current->children[name]->isDirectory) {
            current = current->children[name];
        } else {
            std::cout << "Error: Not found.\n";
        }
    }
};

int main() {
    FileSystem fs;
    fs.mkdir("usr");
    fs.mkdir("bin");
    fs.ls();
    fs.cd("usr");
    fs.mkdir("local");
    fs.ls();
    return 0;
}
