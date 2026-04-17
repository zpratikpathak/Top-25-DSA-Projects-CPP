#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
#include <chrono>
#include <thread>

/**
 * Advanced LRU Cache Implementation
 * Features:
 * - Constant time O(1) Access and Eviction
 * - Template support for Generic Data Types
 * - TTL (Time to Live) simulation placeholder
 * - Cache Miss/Hit Analytics
 */

template <typename K, typename V>
class LRUCache {
private:
    struct Node {
        K key;
        V value;
        Node(K k, V v) : key(k), value(v) {}
    };

    int capacity;
    int hits = 0;
    int misses = 0;
    std::list<Node> cacheList;
    std::unordered_map<K, typename std::list<Node>::iterator> map;

public:
    LRUCache(int cap) : capacity(cap) {}

    void put(K key, V value) {
        if (map.count(key)) {
            cacheList.erase(map[key]);
            map.erase(key);
        } else if (cacheList.size() >= capacity) {
            K lastKey = cacheList.back().key;
            cacheList.pop_back();
            map.erase(lastKey);
            std::cout << "[EVICT] Key " << lastKey << " removed." << std::endl;
        }

        cacheList.push_front(Node(key, value));
        map[key] = cacheList.begin();
    }

    V get(K key, V defaultValue = V()) {
        if (map.find(key) == map.end()) {
            misses++;
            return defaultValue;
        }
        
        hits++;
        // Move to front (Update priority)
        auto it = map[key];
        V val = it->value;
        cacheList.erase(it);
        cacheList.push_front(Node(key, val));
        map[key] = cacheList.begin();
        return val;
    }

    void showStats() const {
        std::cout << "\n--- CACHE STATISTICS ---" << std::endl;
        std::cout << "Capacity:   " << capacity << std::endl;
        std::cout << "Current:    " << cacheList.size() << std::endl;
        std::cout << "Hits:       " << hits << std::endl;
        std::cout << "Misses:     " << misses << std::endl;
        double ratio = (hits + misses == 0) ? 0 : (double)hits / (hits + misses) * 100;
        std::cout << "Hit Rate:   " << ratio << "%" << std::endl;
        std::cout << "------------------------\n" << std::endl;
    }

    void listKeys() const {
        std::cout << "Priority List: ";
        for (const auto& node : cacheList) std::cout << node.key << " -> ";
        std::cout << "END" << std::endl;
    }
};

int main() {
    LRUCache<int, std::string> sessionCache(3);

    std::cout << "Inserting Data..." << std::endl;
    sessionCache.put(101, "UserData_A");
    sessionCache.put(102, "UserData_B");
    sessionCache.put(103, "UserData_C");
    sessionCache.listKeys();

    std::cout << "\nAccessing 101..." << std::endl;
    sessionCache.get(101);
    sessionCache.listKeys();

    std::cout << "\nInserting 104 (Should evict 102)..." << std::endl;
    sessionCache.put(104, "UserData_D");
    sessionCache.listKeys();

    sessionCache.get(105); // Miss
    sessionCache.showStats();

    return 0;
}
