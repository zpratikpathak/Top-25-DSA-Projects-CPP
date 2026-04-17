#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
#include <iomanip>

/**
 * Advanced Inventory Management System
 * Features:
 * - Priority Queue (Max-Heap) for automated restocking alerts
 * - Hash Map for O(1) product lookup
 * - Min/Max inventory threshold monitoring
 * - Batch processing of orders
 */

struct Product {
    int id;
    std::string name;
    int stock;
    int threshold;
    double price;

    bool operator<(const Product& other) const {
        // Priority determined by how far below threshold we are
        return (stock - threshold) > (other.stock - other.threshold);
    }
};

class WarehouseManager {
private:
    std::unordered_map<int, Product> inventory;

public:
    void addProduct(int id, std::string name, int initialStock, int threshold, double price) {
        inventory[id] = {id, name, initialStock, threshold, price};
        std::cout << "[WAREHOUSE] Registered: " << name << " (ID: " << id << ")" << std::endl;
    }

    void updateStock(int id, int change) {
        if (inventory.count(id)) {
            inventory[id].stock += change;
            if (inventory[id].stock < inventory[id].threshold) {
                std::cout << "[ALERT] " << inventory[id].name << " stock is CRITICAL (" << inventory[id].stock << ")" << std::endl;
            }
        }
    }

    void processRestockOrders() {
        std::priority_queue<Product> restockQueue;
        for (auto const& [id, p] : inventory) {
            if (p.stock < p.threshold) restockQueue.push(p);
        }

        std::cout << "\n--- RESTOCK PRIORITY LIST ---" << std::endl;
        while (!restockQueue.empty()) {
            Product p = restockQueue.top(); restockQueue.pop();
            std::cout << "PRIORITY: " << p.name << " | Current: " << p.stock << " | Target: " << p.threshold * 2 << std::endl;
        }
        std::cout << "-----------------------------\n" << std::endl;
    }

    void listInventory() const {
        std::cout << std::left << std::setw(10) << "ID" 
                  << std::setw(20) << "NAME" 
                  << std::setw(10) << "STOCK" 
                  << "PRICE" << std::endl;
        for (auto const& [id, p] : inventory) {
            std::cout << std::left << std::setw(10) << id 
                      << std::setw(20) << p.name 
                      << std::setw(10) << p.stock 
                      << "$" << p.price << std::endl;
        }
    }
};

int main() {
    WarehouseManager wh;

    wh.addProduct(501, "Intel Core i9", 5, 10, 589.99);
    wh.addProduct(502, "NVIDIA RTX 4090", 2, 8, 1599.00);
    wh.addProduct(503, "DDR5 RAM 32GB", 45, 20, 120.00);
    wh.addProduct(504, "NVMe SSD 2TB", 12, 15, 180.00);

    wh.updateStock(501, -2);
    wh.updateStock(502, 1); // some return
    
    wh.listInventory();
    wh.processRestockOrders();

    return 0;
}
