#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <cmath>

/**
 * Advanced Expression Tree Evaluator
 * Features:
 * - Conversion from Infix to Postfix (Shunting-yard Algorithm)
 * - Binary Expression Tree (BET) construction
 * - Recursive and Iterative Tree Traversal
 * - Numerical evaluation support
 */

struct Node {
    std::string value;
    std::shared_ptr<Node> left, right;
    Node(std::string v) : value(v), left(nullptr), right(nullptr) {}
};

class ExpressionEngine {
private:
    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        if (op == '^') return 3;
        return 0;
    }

    bool isOperator(std::string s) {
        return s == "+" || s == "-" || s == "*" || s == "/" || s == "^";
    }

public:
    std::string infixToPostfix(const std::string& infix) {
        std::string postfix = "";
        std::stack<char> st;
        for (char c : infix) {
            if (std::isalnum(c)) postfix += c;
            else if (c == '(') st.push('(');
            else if (c == ')') {
                while (st.top() != '(') { postfix += st.top(); st.pop(); }
                st.pop();
            } else {
                while (!st.empty() && precedence(st.top()) >= precedence(c)) {
                    postfix += st.top(); st.pop();
                }
                st.push(c);
            }
        }
        while (!st.empty()) { postfix += st.top(); st.pop(); }
        return postfix;
    }

    std::shared_ptr<Node> buildTree(const std::string& postfix) {
        std::stack<std::shared_ptr<Node>> st;
        for (char c : postfix) {
            std::string s(1, c);
            if (!isOperator(s)) {
                st.push(std::make_shared<Node>(s));
            } else {
                auto node = std::make_shared<Node>(s);
                node->right = st.top(); st.pop();
                node->left = st.top(); st.pop();
                st.push(node);
            }
        }
        return st.top();
    }

    double evaluate(std::shared_ptr<Node> root) {
        if (!root->left && !root->right) return std::stod(root->value);

        double leftVal = evaluate(root->left);
        double rightVal = evaluate(root->right);

        if (root->value == "+") return leftVal + rightVal;
        if (root->value == "-") return leftVal - rightVal;
        if (root->value == "*") return leftVal * rightVal;
        if (root->value == "/") return leftVal / rightVal;
        if (root->value == "^") return std::pow(leftVal, rightVal);
        return 0;
    }

    void printPrefix(std::shared_ptr<Node> root) {
        if (!root) return;
        std::cout << root->value << " ";
        printPrefix(root->left);
        printPrefix(root->right);
    }
};

int main() {
    ExpressionEngine engine;
    // For simplicity in this demo, values are single digits or variables
    std::string infix = "((3+5)*(2^3))"; 
    
    std::cout << "Infix:   " << infix << std::endl;
    std::string postfix = engine.infixToPostfix(infix);
    std::cout << "Postfix: " << postfix << std::endl;

    auto root = engine.buildTree(postfix);
    std::cout << "Prefix:  ";
    engine.printPrefix(root);
    std::cout << std::endl;

    // Use placeholder numerical values for evaluation if postfix has digits
    try {
        std::cout << "Result:  " << engine.evaluate(root) << std::endl;
    } catch (...) {
        std::cout << "Evaluation skipped (Variables present)" << std::endl;
    }

    return 0;
}
