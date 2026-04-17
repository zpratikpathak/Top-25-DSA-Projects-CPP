#include <iostream>
#include <vector>
#include <climits>

#define INF INT_MAX

class CityGraph {
    int V;
    std::vector<std::vector<int>> dist;

public:
    CityGraph(int v) : V(v), dist(v, std::vector<int>(v, INF)) {
        for(int i=0; i<V; i++) dist[i][i] = 0;
    }

    void addRoute(int u, int v, int w) {
        dist[u][v] = w;
        dist[v][u] = w;
    }

    void floydWarshall() {
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    void print() {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][j] == INF) std::cout << "INF ";
                else std::cout << dist[i][j] << "   ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    CityGraph g(4);
    g.addRoute(0, 1, 5);
    g.addRoute(1, 2, 3);
    g.addRoute(2, 3, 1);
    g.addRoute(0, 3, 10);

    g.floydWarshall();
    g.print();
    return 0;
}
