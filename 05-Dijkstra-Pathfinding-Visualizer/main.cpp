#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Graph {
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void dijkstra(int src) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> dist(V, INT_MAX);

        pq.push({0, src});
        dist[src] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "Vertex Distance from Source\n";
        for (int i = 0; i < V; ++i)
            cout << i << " \t\t " << dist[i] << "\n";
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1, 9);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(0, 4, 3);
    g.addEdge(2, 1, 2);
    g.addEdge(2, 3, 4);

    g.dijkstra(0);
    return 0;
}
