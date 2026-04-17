#include <iostream>
#include <vector>
#include <list>
#include <iomanip>
#include <string>

/**
 * Advanced Memory Allocator Simulator
 * Features:
 * - Best-Fit and First-Fit allocation policies
 * - Block splitting to minimize internal fragmentation
 * - Memory coalescing (merging adjacent free blocks)
 * - Visualization of memory map
 */

struct MemoryBlock {
    size_t offset;
    size_t size;
    bool isFree;
    std::string owner;

    MemoryBlock(size_t o, size_t s, bool f, std::string name = "") 
        : offset(o), size(s), isFree(f), owner(name) {}
};

class AllocatorSim {
private:
    size_t totalCapacity;
    std::list<MemoryBlock> heap;

    void coalesce() {
        auto it = heap.begin();
        while (it != heap.end()) {
            auto next = std::next(it);
            if (next != heap.end() && it->isFree && next->isFree) {
                it->size += next->size;
                heap.erase(next);
            } else {
                ++it;
            }
        }
    }

public:
    AllocatorSim(size_t size) : totalCapacity(size) {
        heap.push_back(MemoryBlock(0, size, true));
    }

    void allocate(size_t size, std::string owner, bool bestFit = true) {
        auto bestIt = heap.end();
        size_t minFragment = totalCapacity + 1;

        for (auto it = heap.begin(); it != heap.end(); ++it) {
            if (it->isFree && it->size >= size) {
                if (!bestFit) { // First fit
                    bestIt = it;
                    break;
                }
                if (it->size - size < minFragment) {
                    minFragment = it->size - size;
                    bestIt = it;
                }
            }
        }

        if (bestIt == heap.end()) {
            std::cout << "[ERROR] Out of memory for " << owner << " (" << size << " bytes)" << std::endl;
            return;
        }

        size_t originalSize = bestIt->size;
        size_t offset = bestIt->offset;

        bestIt->isFree = false;
        bestIt->size = size;
        bestIt->owner = owner;

        if (originalSize > size) {
            heap.insert(std::next(bestIt), MemoryBlock(offset + size, originalSize - size, true));
        }

        std::cout << "[ALLOC] " << owner << " assigned " << size << " bytes at offset " << offset << std::endl;
    }

    void deallocate(std::string owner) {
        bool found = false;
        for (auto& block : heap) {
            if (block.owner == owner) {
                block.isFree = true;
                block.owner = "";
                found = true;
            }
        }
        if (found) {
            std::cout << "[FREE] Released memory owned by " << owner << std::endl;
            coalesce();
        }
    }

    void displayMap() const {
        std::cout << "\n--- MEMORY MAP (" << totalCapacity << " bytes) ---" << std::endl;
        for (const auto& b : heap) {
            std::cout << "[" << std::setw(4) << b.offset << " | " << std::setw(4) << b.size << "B] ";
            if (b.isFree) std::cout << "FREE (Fragment)";
            else std::cout << "USED BY: " << b.owner;
            std::cout << std::endl;
        }
        std::cout << "------------------------------------------\n" << std::endl;
    }
};

int main() {
    AllocatorSim kernel(1024);

    kernel.allocate(256, "Process_Alpha");
    kernel.allocate(128, "Process_Beta");
    kernel.allocate(64, "Driver_Network");
    kernel.displayMap();

    kernel.deallocate("Process_Beta");
    kernel.displayMap(); // Shows hole

    kernel.allocate(32, "Process_Gamma", true); // Should use Best Fit to minimize hole waste
    kernel.displayMap();

    kernel.deallocate("Process_Alpha");
    kernel.deallocate("Driver_Network"); // Should coalesce everything back
    kernel.displayMap();

    return 0;
}
