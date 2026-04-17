#include <iostream>
#include <stack>
#include <string>

struct Node {
    char data;
    Node *left, *right;
    Node(char d) : data(d), left(nullptr), right(nullptr) {}
};

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

void inorder(Node* t) {
    if (t) {
        inorder(t->left);
        std::cout << t->data << " ";
        inorder(t->right);
    }
}

Node* constructTree(std::string postfix) {
    std::stack<Node*> st;
    for (char c : postfix) {
        if (!isOperator(c)) {
            st.push(new Node(c));
        } else {
            Node* t = new Node(c);
            t->right = st.top(); st.pop();
            t->left = st.top(); st.pop();
            st.push(t);
        }
    }
    return st.top();
}

int main() {
    std::string postfix = "ab+ef*g*-";
    Node* root = constructTree(postfix);
    std::cout << "Inorder Traversal: ";
    inorder(root);
    std::cout << "\n";
    return 0;
}
