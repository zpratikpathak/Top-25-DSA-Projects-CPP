#include <iostream>
#include <string>

struct Node {
    int bookID;
    std::string title;
    Node *left, *right;
    
    Node(int id, std::string t) : bookID(id), title(t), left(nullptr), right(nullptr) {}
};

class Library {
    Node* root;

    Node* insert(Node* node, int id, std::string title) {
        if (!node) return new Node(id, title);
        if (id < node->bookID) node->left = insert(node->left, id, title);
        else if (id > node->bookID) node->right = insert(node->right, id, title);
        return node;
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        std::cout << "ID: " << node->bookID << " | Title: " << node->title << "\n";
        inorder(node->right);
    }

public:
    Library() : root(nullptr) {}
    void addBook(int id, std::string title) { root = insert(root, id, title); }
    void showInventory() {
        std::cout << "\n--- Library Inventory ---\n";
        inorder(root);
    }
};

int main() {
    Library lib;
    lib.addBook(105, "The C++ Programming Language");
    lib.addBook(101, "Introduction to Algorithms");
    lib.addBook(110, "Design Patterns");
    lib.showInventory();
    return 0;
}
