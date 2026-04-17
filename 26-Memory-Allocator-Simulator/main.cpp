#include <iostream>
#include <vector>

struct Block {
    int size;
    bool free;
    Block(int s) : size(s), free(true) {}
};

class MemoryAllocator {
    std::vector<Block> blocks;

public:
    MemoryAllocator() {
        blocks.push_back(Block(1024)); // Initial pool
    }

    void allocate(int size) {
        for (auto& b : blocks) {
            if (b.free && b.size >= size) {
                if (b.size > size) {
                    int remaining = b.size - size;
                    b.size = size;
                    b.free = false;
                    blocks.push_back(Block(remaining));
                } else {
                    b.free = false;
                }
                std::cout << "Allocated " << size << " bytes.\n";
                return;
            }
        }
        std::cout << "Allocation failed: Out of memory.\n";
    }

    void showStatus() {
        std::cout << "Memory Status: ";
        for (auto const& b : blocks) {
            std::cout << "[" << b.size << " bytes, " << (b.free ? "Free" : "Used") << "] ";
        }
        std::cout << "\n";
    }
};

int main() {
    MemoryAllocator ma;
    ma.showStatus();
    ma.allocate(256);
    ma.showStatus();
    ma.allocate(2000);
    return 0;
}
