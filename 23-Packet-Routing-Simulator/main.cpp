#include <iostream>
#include <vector>
#include <queue>
#include <map>

class Router {
    std::map<int, std::vector<int>> adj;

public:
    void addLink(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void findRoute(int src, int dest) {
        std::queue<std::vector<int>> q;
        q.push({src});
        std::map<int, bool> visited;
        visited[src] = true;

        while (!q.empty()) {
            std::vector<int> path = q.front(); q.pop();
            int node = path.back();

            if (node == dest) {
                std::cout << "Packet Route: ";
                for (int n : path) std::cout << n << " -> ";
                std::cout << "DONE\n";
                return;
            }

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    std::vector<int> newPath = path;
                    newPath.push_back(neighbor);
                    q.push(newPath);
                }
            }
        }
        std::cout << "No route found.\n";
    }
};

int main() {
    Router net;
    net.addLink(1, 2);
    net.addLink(2, 3);
    net.addLink(3, 4);
    net.addLink(1, 4);

    net.findRoute(1, 3);
    return 0;
}
