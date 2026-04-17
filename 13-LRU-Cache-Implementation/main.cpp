#include <iostream>
#include <unordered_map>
#include <list>

class LRUCache {
    int capacity;
    std::list<int> dq;
    std::unordered_map<int, std::pair<int, std::list<int>::iterator>> ma;

public:
    LRUCache(int n) : capacity(n) {}

    void put(int key, int value) {
        if (ma.find(key) == ma.end()) {
            if (dq.size() == capacity) {
                int last = dq.back();
                dq.pop_back();
                ma.erase(last);
            }
        } else {
            dq.erase(ma[key].second);
        }
        dq.push_front(key);
        ma[key] = {value, dq.begin()};
    }

    int get(int key) {
        if (ma.find(key) == ma.end()) return -1;
        dq.erase(ma[key].second);
        dq.push_front(key);
        ma[key].second = dq.begin();
        return ma[key].first;
    }

    void display() {
        std::cout << "Cache Content (Key): ";
        for (auto const& i : dq) std::cout << i << " ";
        std::cout << "\n";
    }
};

int main() {
    LRUCache cache(3);
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    cache.display();
    cache.get(1);
    cache.put(4, 40);
    cache.display();
    return 0;
}
