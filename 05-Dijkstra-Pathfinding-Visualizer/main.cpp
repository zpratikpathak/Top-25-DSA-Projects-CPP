#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <map>
#include <string>
#include <algorithm>

/**
 * Advanced Dijkstra Pathfinding Visualizer
 * Features:
 * - Adjacency List with Priority Queue optimization: O((V+E) log V)
 * - Support for named locations (Cities/Nodes)
 * - Path reconstruction and distance metrics
 * - Edge case handling for disconnected components
 */

struct Edge {
    int to;
    int weight;
};

class Navigator {
private:
    int numNodes;
    std::vector<std::vector<Edge>> adj;
    std::map<std::string, int> nameToIndex;
    std::map<int, std::string> indexToName;

public:
    Navigator() : numNodes(0) {}

    void addLocation(const std::string& name) {
        if (nameToIndex.find(name) == nameToIndex.end()) {
            nameToIndex[name] = numNodes;
            indexToName[numNodes] = name;
            adj.push_back({});
            numNodes++;
        }
    }

    void addRoute(const std::string& u, const std::string& v, int w) {
        addLocation(u);
        addLocation(v);
        adj[nameToIndex[u]].push_back({nameToIndex[v], w});
        adj[nameToIndex[v]].push_back({nameToIndex[u], w}); // Undirected
    }

    void findShortestPath(const std::string& startNode, const std::string& endNode) {
        if (!nameToIndex.count(startNode) || !nameToIndex.count(endNode)) {
            std::cout << "[ERROR] Invalid locations." << std::endl;
            return;
        }

        int start = nameToIndex[startNode];
        int target = nameToIndex[endNode];

        std::vector<int> dist(numNodes, INT_MAX);
        std::vector<int> parent(numNodes, -1);
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d > dist[u]) continue;
            if (u == target) break;

            for (const auto& edge : adj[u]) {
                if (dist[u] + edge.weight < dist[edge.to]) {
                    dist[edge.to] = dist[u] + edge.weight;
                    parent[edge.to] = u;
                    pq.push({dist[edge.to], edge.to});
                }
            }
        }

        if (dist[target] == INT_MAX) {
            std::cout << "No path exists between " << startNode << " and " << endNode << std::endl;
        } else {
            std::cout << "\n--- SHORTEST PATH FOUND ---" << std::endl;
            std::cout << "Total Distance: " << dist[target] << " units" << std::endl;
            
            std::vector<std::string> path;
            for (int v = target; v != -1; v = parent[v]) {
                path.push_back(indexToName[v]);
            }
            std::reverse(path.begin(), path.end());

            std::cout << "Route: ";
            for (size_t i = 0; i < path.size(); ++i) {
                std::cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
            }
            std::cout << "\n---------------------------\n" << std::endl;
        }
    }
};

int main() {
    Navigator gps;

    // Build a complex city map
    gps.addRoute("Delhi", "Jaipur", 280);
    gps.addRoute("Delhi", "Agra", 230);
    gps.addRoute("Jaipur", "Ahmedabad", 670);
    gps.addRoute("Agra", "Lucknow", 330);
    gps.addRoute("Lucknow", "Patna", 500);
    gps.addRoute("Ahmedabad", "Mumbai", 530);
    gps.addRoute("Mumbai", "Pune", 150);
    gps.addRoute("Pune", "Bangalore", 840);
    gps.addRoute("Patna", "Kolkata", 600);
    gps.addRoute("Bangalore", "Chennai", 350);
    gps.addRoute("Delhi", "Chandigarh", 250);

    gps.findShortestPath("Delhi", "Mumbai");
    gps.findShortestPath("Lucknow", "Chennai");

    return 0;
}
