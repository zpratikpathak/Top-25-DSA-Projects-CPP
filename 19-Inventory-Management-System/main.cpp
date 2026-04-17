#include <iostream>
#include <vector>
#include <queue>
#include <string>

struct Item {
    int id;
    std::string name;
    int priority;

    bool operator<(const Item& other) const {
        return priority < other.priority; // Max-Heap based on priority
    }
};

class Inventory {
    std::priority_queue<Item> pq;

public:
    void addItem(int id, std::string name, int priority) {
        pq.push({id, name, priority});
    }

    void processItem() {
        if (!pq.empty()) {
            Item top = pq.top();
            std::cout << "Processing: " << top.name << " (Priority: " << top.priority << ")\n";
            pq.pop();
        } else {
            std::cout << "Inventory empty.\n";
        }
    }
};

int main() {
    Inventory inv;
    inv.addItem(1, "Product A", 10);
    inv.addItem(2, "Product B", 50);
    inv.addItem(3, "Product C", 20);

    inv.processItem();
    inv.processItem();
    return 0;
}
