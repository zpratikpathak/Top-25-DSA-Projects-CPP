#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>

class SocialNetwork {
    std::map<std::string, std::set<std::string>> adj;

public:
    void addUser(std::string name) {
        if (adj.find(name) == adj.end()) adj[name] = {};
    }

    void addFriendship(std::string u, std::string v) {
        adj[u].insert(v);
        adj[v].insert(u);
    }

    void findMutualFriends(std::string u, std::string v) {
        std::cout << "Mutual friends between " << u << " and " << v << ": ";
        for (auto const& friend_name : adj[u]) {
            if (adj[v].count(friend_name)) {
                std::cout << friend_name << " ";
            }
        }
        std::cout << "\n";
    }

    void suggestFriends(std::string user) {
        std::cout << "Friend suggestions for " << user << ": ";
        std::map<std::string, int> counts;
        for (auto const& friend_name : adj[user]) {
            for (auto const& fof : adj[friend_name]) {
                if (fof != user && !adj[user].count(fof)) {
                    counts[fof]++;
                }
            }
        }
        for (auto const& [name, count] : counts) {
            std::cout << name << "(" << count << " mutual) ";
        }
        std::cout << "\n";
    }
};

int main() {
    SocialNetwork sn;
    sn.addUser("Pratik");
    sn.addUser("Alice");
    sn.addUser("Bob");
    sn.addUser("Charlie");

    sn.addFriendship("Pratik", "Alice");
    sn.addFriendship("Alice", "Bob");
    sn.addFriendship("Bob", "Charlie");
    sn.addFriendship("Pratik", "Charlie");

    sn.findMutualFriends("Pratik", "Bob");
    sn.suggestFriends("Alice");
    return 0;
}
