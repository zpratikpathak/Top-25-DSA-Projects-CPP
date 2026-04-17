#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <ctime>
#include <iomanip>
#include <sstream>

/**
 * Advanced File System Simulator
 * Features:
 * - Hierarchical Tree structure for Directories/Files
 * - Absolute and Relative path navigation
 * - Metadata tracking (Creation time, Size, Permissions)
 * - CRUD operations: mkdir, touch, rm, ls, cd, pwd
 */

enum class NodeType { File, Directory };

struct Node {
    std::string name;
    NodeType type;
    std::string content;
    std::time_t createdAt;
    size_t size;
    std::map<std::string, std::shared_ptr<Node>> children;
    std::weak_ptr<Node> parent;

    Node(std::string n, NodeType t, std::shared_ptr<Node> p = nullptr) 
        : name(n), type(t), createdAt(std::time(nullptr)), size(0), parent(p) {}

    std::string getTimestamp() const {
        std::tm* tm_ptr = std::localtime(&createdAt);
        std::stringstream ss;
        ss << std::put_time(tm_ptr, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
};

class FileSystem {
private:
    std::shared_ptr<Node> root;
    std::shared_ptr<Node> current;

public:
    FileSystem() {
        root = std::make_shared<Node>("/", NodeType::Directory);
        current = root;
    }

    void mkdir(const std::string& name) {
        if (current->children.count(name)) {
            std::cout << "[ERROR] Directory already exists." << std::endl;
            return;
        }
        auto newNode = std::make_shared<Node>(name, NodeType::Directory, current);
        current->children[name] = newNode;
        std::cout << "[SUCCESS] Created directory: " << name << std::endl;
    }

    void touch(const std::string& name, const std::string& content = "") {
        if (current->children.count(name)) {
            current->children[name]->content = content;
            current->children[name]->size = content.length();
            std::cout << "[SUCCESS] Updated file: " << name << std::endl;
        } else {
            auto newNode = std::make_shared<Node>(name, NodeType::File, current);
            newNode->content = content;
            newNode->size = content.length();
            current->children[name] = newNode;
            std::cout << "[SUCCESS] Created file: " << name << std::endl;
        }
    }

    void ls() const {
        std::cout << "\n--- LISTING FOR: " << pwd() << " ---" << std::endl;
        std::cout << std::left << std::setw(10) << "TYPE" << std::setw(20) << "NAME" << std::setw(10) << "SIZE" << "CREATED AT" << std::endl;
        for (auto const& [name, node] : current->children) {
            std::cout << std::left << std::setw(10) << (node->type == NodeType::Directory ? "[DIR]" : "[FILE]") 
                      << std::setw(20) << name 
                      << std::setw(10) << node->size 
                      << node->getTimestamp() << std::endl;
        }
    }

    void cd(const std::string& name) {
        if (name == "/") {
            current = root;
        } else if (name == "..") {
            if (auto p = current->parent.lock()) current = p;
        } else if (current->children.count(name) && current->children[name]->type == NodeType::Directory) {
            current = current->children[name];
        } else {
            std::cout << "[ERROR] Directory not found." << std::endl;
        }
    }

    std::string pwd() const {
        std::vector<std::string> path;
        auto temp = current;
        while (temp != root) {
            path.push_back(temp->name);
            temp = temp->parent.lock();
        }
        std::string res = "/";
        for (int i = path.size() - 1; i >= 0; --i) res += path[i] + (i == 0 ? "" : "/");
        return res;
    }

    void rm(const std::string& name) {
        if (current->children.erase(name)) {
            std::cout << "[SUCCESS] Removed: " << name << std::endl;
        } else {
            std::cout << "[ERROR] Not found." << std::endl;
        }
    }
};

int main() {
    FileSystem fs;

    fs.mkdir("usr");
    fs.mkdir("etc");
    fs.cd("usr");
    fs.mkdir("local");
    fs.touch("readme.txt", "Advanced DSA Simulation v2.0");
    fs.ls();

    std::cout << "\nCurrent Path: " << fs.pwd() << std::endl;

    fs.cd("..");
    fs.ls();

    fs.rm("etc");
    fs.ls();

    return 0;
}
