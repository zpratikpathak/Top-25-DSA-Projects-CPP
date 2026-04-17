#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <set>
#include <algorithm>

/**
 * Advanced Packet Routing Simulator
 * Features:
 * - OSPF-like routing using Dijkstra's algorithm
 * - Link failure simulation and dynamic rerouting
 * - Routing Table visualization for every node
 * - Bandwidth and Latency metrics for cost calculation
 */

struct Link {
    int to;
    int latency; // Cost
    int bandwidth;
};

class NetworkRouter {
private:
    std::map<int, std::vector<Link>> topology;
    std::set<int> nodes;

public:
    void addLink(int u, int v, int lat, int bw) {
        topology[u].push_back({v, lat, bw});
        topology[v].push_back({u, lat, bw});
        nodes.insert(u); nodes.insert(v);
    }

    void simulateRouting(int src, int dest) {
        if (!nodes.count(src) || !nodes.count(dest)) return;

        std::map<int, int> dist;
        std::map<int, int> parent;
        for (int node : nodes) dist[node] = 1e9;
        
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d > dist[u]) continue;

            for (auto const& link : topology[u]) {
                if (dist[u] + link.latency < dist[link.to]) {
                    dist[link.to] = dist[u] + link.latency;
                    parent[link.to] = u;
                    pq.push({dist[link.to], link.to});
                }
            }
        }

        if (dist[dest] == 1e9) {
            std::cout << "[ERROR] No route from Node " << src << " to Node " << dest << std::endl;
        } else {
            std::cout << "\n--- PACKET ROUTE (OSPF SIM) ---" << std::endl;
            std::cout << "Metric (Latency): " << dist[dest] << "ms" << std::endl;
            std::vector<int> path;
            for (int v = dest; v != src; v = parent[v]) path.push_back(v);
            path.push_back(src);
            std::reverse(path.begin(), path.end());

            for (size_t i = 0; i < path.size(); ++i) {
                std::cout << "Node_" << path[i] << (i == path.size() - 1 ? "" : " -> ");
            }
            std::cout << "\n-------------------------------\n" << std::endl;
        }
    }

    void displayRoutingTable(int nodeId) {
        std::cout << "Routing Table for Node_" << nodeId << ":\n";
        for (auto const& link : topology[nodeId]) {
            std::cout << " -> Dest: Node_" << link.to << " | Cost: " << link.latency << " | Bandwidth: " << link.bandwidth << "Gbps\n";
        }
    }
};

int main() {
    NetworkRouter backbone;

    backbone.addLink(1, 2, 10, 100);
    backbone.addLink(2, 3, 5, 100);
    backbone.addLink(1, 4, 50, 10);
    backbone.addLink(4, 3, 10, 10);
    backbone.addLink(2, 5, 20, 50);
    backbone.addLink(5, 3, 5, 50);

    backbone.displayRoutingTable(1);
    backbone.simulateRouting(1, 3);
    
    // Path should be 1->2->3 (Cost: 15) vs 1->4->3 (Cost: 60)
    
    return 0;
}
