#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <string>
#include <algorithm>
#include <iomanip>

/**
 * Advanced Social Network Analysis
 * Features:
 * - Graph implementation using Adjacency Lists (std::map)
 * - BFS for Degrees of Separation (Shortest Path)
 * - Influence analysis using Degree Centrality
 * - Mutual friendship recommendation algorithm
 */

class SocialGraph {
private:
    std::map<std::string, std::set<std::string>> adj;

public:
    void addUser(const std::string& name) {
        if (adj.find(name) == adj.end()) adj[name] = {};
    }

    void addFriendship(const std::string& u, const std::string& v) {
        addUser(u); addUser(v);
        adj[u].insert(v);
        adj[v].insert(u);
    }

    int getDegreesOfSeparation(const std::string& start, const std::string& target) {
        if (start == target) return 0;
        if (!adj.count(start) || !adj.count(target)) return -1;

        std::queue<std::pair<std::string, int>> q;
        std::set<std::string> visited;
        
        q.push({start, 0});
        visited.insert(start);

        while (!q.empty()) {
            auto [curr, dist] = q.front(); q.pop();
            if (curr == target) return dist;

            for (const auto& neighbor : adj[curr]) {
                if (!visited.count(neighbor)) {
                    visited.insert(neighbor);
                    q.push({neighbor, dist + 1});
                }
            }
        }
        return -1; // Disconnected
    }

    void recommendFriends(const std::string& user) {
        if (!adj.count(user)) return;
        
        std::map<std::string, int> mutualCount;
        for (const auto& friend_name : adj[user]) {
            for (const auto& fof : adj[friend_name]) {
                if (fof != user && !adj[user].count(fof)) {
                    mutualCount[fof]++;
                }
            }
        }

        std::vector<std::pair<int, std::string>> sorted;
        for (auto const& [name, count] : mutualCount) sorted.push_back({count, name});
        std::sort(sorted.rbegin(), sorted.rend());

        std::cout << "\n--- RECOMMENDATIONS FOR " << user << " ---" << std::endl;
        for (auto const& [count, name] : sorted) {
            std::cout << name << " (" << count << " mutual friends)" << std::endl;
        }
    }

    void displayInfluenceRank() {
        std::vector<std::pair<int, std::string>> ranks;
        for (auto const& [user, friends] : adj) {
            ranks.push_back({(int)friends.size(), user});
        }
        std::sort(ranks.rbegin(), ranks.rend());

        std::cout << "\n--- INFLUENCE RANK (DEGREE CENTRALITY) ---" << std::endl;
        for (auto const& [score, user] : ranks) {
            std::cout << std::left << std::setw(15) << user << " Friends: " << score << std::endl;
        }
    }
};

int main() {
    SocialGraph net;

    // Build complex network
    net.addFriendship("Pratik", "Alice");
    net.addFriendship("Pratik", "Bob");
    net.addFriendship("Alice", "Charlie");
    net.addFriendship("Bob", "Charlie");
    net.addFriendship("Charlie", "David");
    net.addFriendship("David", "Eve");
    net.addFriendship("Eve", "Frank");
    net.addFriendship("Frank", "Grace");
    net.addFriendship("Grace", "Heidi");
    net.addFriendship("Alice", "Frank"); // shortcut

    net.displayInfluenceRank();
    
    std::cout << "\nDegrees of Separation (Pratik -> Heidi): " 
              << net.getDegreesOfSeparation("Pratik", "Heidi") << std::endl;

    net.recommendFriends("Pratik");

    return 0;
}
