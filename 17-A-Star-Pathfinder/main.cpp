#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <map>

/**
 * Advanced A* Pathfinder
 * Features:
 * - Optimized A* Search Algorithm with Heuristics
 * - Support for Obstacles (Grid-based)
 * - Manhattan and Euclidean Distance Heuristics
 * - Path reconstruction with direction metadata
 */

struct Node {
    int r, c;
    double g, h;
    Node* parent;

    Node(int r, int c, double g = 0, double h = 0, Node* p = nullptr) 
        : r(r), c(c), g(g), h(h), parent(p) {}
    
    double f() const { return g + h; }
    
    bool operator>(const Node& other) const {
        return f() > other.f();
    }
};

struct CompareNode {
    bool operator()(Node* a, Node* b) { return *a > *b; }
};

class GridNavigator {
private:
    int rows, cols;
    std::vector<std::vector<int>> grid; // 0: Path, 1: Obstacle

    double heuristic(int r1, int c1, int r2, int c2) {
        return std::sqrt(std::pow(r1 - r2, 2) + std::pow(c1 - c2, 2)); // Euclidean
    }

public:
    GridNavigator(int r, int c) : rows(r), cols(c), grid(r, std::vector<int>(c, 0)) {}

    void addObstacle(int r, int c) { if (r >= 0 && r < rows && c >= 0 && c < cols) grid[r][c] = 1; }

    void findPath(int startR, int startC, int endR, int endC) {
        std::priority_queue<Node*, std::vector<Node*>, CompareNode> open;
        std::map<std::pair<int, int>, double> visited;
        
        open.push(new Node(startR, startC, 0, heuristic(startR, startC, endR, endC)));
        
        Node* target = nullptr;

        while(!open.empty()) {
            Node* curr = open.top(); open.pop();

            if (curr->r == endR && curr->c == endC) {
                target = curr;
                break;
            }

            // Directions: 8-way movement
            for(int dr = -1; dr <= 1; ++dr) {
                for(int dc = -1; dc <= 1; ++dc) {
                    if (dr == 0 && dc == 0) continue;
                    
                    int nr = curr->r + dr;
                    int nc = curr->c + dc;

                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == 0) {
                        double newG = curr->g + ((dr != 0 && dc != 0) ? 1.414 : 1.0);
                        
                        if (visited.find({nr, nc}) == visited.end() || visited[{nr, nc}] > newG) {
                            visited[{nr, nc}] = newG;
                            open.push(new Node(nr, nc, newG, heuristic(nr, nc, endR, endC), curr));
                        }
                    }
                }
            }
        }

        if (target) {
            std::cout << "\n--- A* PATH FOUND (Distance: " << target->g << ") ---" << std::endl;
            std::vector<std::pair<int, int>> path;
            while(target) {
                path.push_back({target->r, target->c});
                target = target->parent;
            }
            std::reverse(path.begin(), path.end());
            for(auto const& p : path) std::cout << "(" << p.first << "," << p.second << ") ";
            std::cout << "\n---------------------------\n" << std::endl;
        } else {
            std::cout << "[SYSTEM] No viable path found." << std::endl;
        }
    }
};

int main() {
    GridNavigator nav(10, 10);
    
    // Create a "U" shaped wall
    for(int i = 2; i < 8; ++i) nav.addObstacle(i, 5);
    for(int j = 2; j < 6; ++j) nav.addObstacle(7, j);

    nav.findPath(0, 0, 9, 9);

    return 0;
}
