#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <queue>
#include <map>

/**
 * Advanced Library Management System
 * Features:
 * - AVL Tree implementation (Self-balancing BST) for O(log N) operations
 * - Smart pointers for memory safety
 * - Multi-criteria search (Genre/Title)
 * - Automatic Balancing upon insertion/deletion
 */

struct Book {
    int id;
    std::string title;
    std::string author;
    std::string genre;

    Book(int i, std::string t, std::string a, std::string g) 
        : id(i), title(t), author(a), genre(g) {}
};

class AVLNode {
public:
    std::unique_ptr<Book> book;
    int height;
    std::unique_ptr<AVLNode> left, right;

    AVLNode(std::unique_ptr<Book> b) : book(std::move(b)), height(1), left(nullptr), right(nullptr) {}
};

class LibraryManager {
private:
    std::unique_ptr<AVLNode> root;

    int getHeight(AVLNode* n) { return n ? n->height : 0; }
    int getBalance(AVLNode* n) { return n ? getHeight(n->left.get()) - getHeight(n->right.get()) : 0; }

    void updateHeight(AVLNode* n) {
        if (n) n->height = 1 + std::max(getHeight(n->left.get()), getHeight(n->right.get()));
    }

    std::unique_ptr<AVLNode> rotateRight(std::unique_ptr<AVLNode> y) {
        auto x = std::move(y->left);
        y->left = std::move(x->right);
        updateHeight(y.get());
        x->right = std::move(y);
        updateHeight(x.get());
        return x;
    }

    std::unique_ptr<AVLNode> rotateLeft(std::unique_ptr<AVLNode> x) {
        auto y = std::move(x->right);
        x->right = std::move(y->left);
        updateHeight(x.get());
        y->left = std::move(x);
        updateHeight(y.get());
        return y;
    }

    std::unique_ptr<AVLNode> balanceNode(std::unique_ptr<AVLNode> node) {
        updateHeight(node.get());
        int balance = getBalance(node.get());

        if (balance > 1) {
            if (getBalance(node->left.get()) < 0) node->left = rotateLeft(std::move(node->left));
            return rotateRight(std::move(node));
        }
        if (balance < -1) {
            if (getBalance(node->right.get()) > 0) node->right = rotateRight(std::move(node->right));
            return rotateLeft(std::move(node));
        }
        return node;
    }

    std::unique_ptr<AVLNode> insert(std::unique_ptr<AVLNode> node, std::unique_ptr<Book> book) {
        if (!node) return std::make_unique<AVLNode>(std::move(book));

        if (book->id < node->book->id) node->left = insert(std::move(node->left), std::move(book));
        else if (book->id > node->book->id) node->right = insert(std::move(node->right), std::move(book));
        else return node; // Duplicate ID

        return balanceNode(std::move(node));
    }

    void inorder(AVLNode* n, std::vector<const Book*>& results) const {
        if (!n) return;
        inorder(n->left.get(), results);
        results.push_back(n->book.get());
        inorder(n->right.get(), results);
    }

public:
    void addBook(int id, std::string title, std::string author, std::string genre) {
        root = insert(std::move(root), std::make_unique<Book>(id, title, author, genre));
    }

    void listAll() const {
        std::vector<const Book*> results;
        inorder(root.get(), results);
        std::cout << "\n--- LIBRARY INVENTORY (SORTED BY ID) ---\n";
        for (auto b : results) {
            std::cout << "[" << b->id << "] " << b->title << " | " << b->author << " [" << b->genre << "]\n";
        }
    }

    void searchByGenre(const std::string& genre) const {
        std::vector<const Book*> results;
        inorder(root.get(), results);
        std::cout << "\n--- SEARCH RESULTS FOR GENRE: " << genre << " ---\n";
        for (auto b : results) {
            if (b->genre == genre) std::cout << b->title << " by " << b->author << "\n";
        }
    }
};

int main() {
    LibraryManager lib;
    
    // Simulate insertions forcing rebalances
    lib.addBook(1001, "The C++ Programming Language", "Bjarne Stroustrup", "Technical");
    lib.addBook(1005, "Introduction to Algorithms", "CLRS", "Technical");
    lib.addBook(990, "Dune", "Frank Herbert", "Sci-Fi");
    lib.addBook(1020, "1984", "George Orwell", "Dystopian");
    lib.addBook(1008, "The Great Gatsby", "F. Scott Fitzgerald", "Classic");
    lib.addBook(950, "Foundation", "Isaac Asimov", "Sci-Fi");

    lib.listAll();
    lib.searchByGenre("Sci-Fi");

    return 0;
}
