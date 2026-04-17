#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

struct Node {
    int x, y;
    int g, h;
    Node* parent;

    Node(int x, int y, int g = 0, int h = 0, Node* p = nullptr) : x(x), y(y), g(g), h(h), parent(p) {}
    int f() const { return g + h; }
};

struct CompareNode {
    bool operator()(Node* a, Node* b) { return a->f() > b->f(); }
};

int heuristic(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

void aStar(int startX, int startY, int endX, int endY) {
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> openList;
    openList.push(new Node(startX, startY, 0, heuristic(startX, startY, endX, endY)));

    while (!openList.empty()) {
        Node* curr = openList.top(); openList.pop();

        if (curr->x == endX && curr->y == endY) {
            std::cout << "Path found!\n";
            return;
        }

        // Simplification: add neighbors logic here
        // For demonstration, we just exit after finding the node
    }
}

int main() {
    std::cout << "A* Pathfinder initialized.\n";
    aStar(0, 0, 5, 5);
    return 0;
}
