#include <iostream>
#include <vector>
#include <climits>
#include <string>
#include <map>
#include <iomanip>

/**
 * Advanced Shortest Path in Cities
 * Features:
 * - Floyd-Warshall implementation: O(V^3) All-Pairs Shortest Path
 * - Support for named City nodes
 * - Detection of unreachable cities
 * - Formatted adjacency matrix visualization
 */

class TransitSystem {
private:
    int V;
    std::vector<std::vector<int>> dist;
    std::map<int, std::string> indexToCity;
    std::map<std::string, int> cityToIndex;
    const int INF = 1e6; // Large value that won't overflow during addition

public:
    TransitSystem(const std::vector<std::string>& cities) : V(cities.size()) {
        dist.assign(V, std::vector<int>(V, INF));
        for (int i = 0; i < V; ++i) {
            dist[i][i] = 0;
            indexToCity[i] = cities[i];
            cityToIndex[cities[i]] = i;
        }
    }

    void addRoute(const std::string& u, const std::string& v, int w) {
        if (cityToIndex.count(u) && cityToIndex.count(v)) {
            int i = cityToIndex[u], j = cityToIndex[v];
            dist[i][j] = w;
            dist[j][i] = w;
        }
    }

    void computeAllPairs() {
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    void displayMatrix() const {
        std::cout << "\n--- GLOBAL TRANSIT DISTANCE MATRIX ---\n";
        std::cout << std::setw(12) << " ";
        for(int i=0; i<V; i++) std::cout << std::setw(12) << indexToCity.at(i).substr(0, 10);
        std::cout << "\n";

        for (int i = 0; i < V; i++) {
            std::cout << std::setw(12) << indexToCity.at(i).substr(0, 10);
            for (int j = 0; j < V; j++) {
                if (dist[i][j] >= INF) std::cout << std::setw(12) << "INF";
                else std::cout << std::setw(12) << dist[i][j];
            }
            std::cout << "\n";
        }
        std::cout << "--------------------------------------\n" << std::endl;
    }

    void getDistance(const std::string& u, const std::string& v) {
        if (cityToIndex.count(u) && cityToIndex.count(v)) {
            int d = dist[cityToIndex[u]][cityToIndex[v]];
            std::cout << "[TRANSIT] Distance from " << u << " to " << v << ": ";
            if (d >= INF) std::cout << "UNREACHABLE" << std::endl;
            else std::cout << d << " units" << std::endl;
        }
    }
};

int main() {
    std::vector<std::string> cities = {"London", "Paris", "Berlin", "Rome", "Madrid"};
    TransitSystem europe(cities);

    europe.addRoute("London", "Paris", 340);
    europe.addRoute("Paris", "Berlin", 1050);
    europe.addRoute("Berlin", "Rome", 1500);
    europe.addRoute("Rome", "Paris", 1100);
    europe.addRoute("Madrid", "Paris", 1200);

    europe.computeAllPairs();
    europe.displayMatrix();
    
    europe.getDistance("London", "Rome");
    europe.getDistance("London", "Madrid");

    return 0;
}
