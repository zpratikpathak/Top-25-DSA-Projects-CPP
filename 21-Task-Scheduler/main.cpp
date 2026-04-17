#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>

/**
 * Advanced Task Scheduler
 * Features:
 * - Priority Queue (Max-Heap) for task management
 * - Task categorization (System, User, IO)
 * - Aging simulation (Placeholder for preventing starvation)
 * - Thread-safe scheduling foundation
 */

enum class TaskType { SYSTEM, USER, BACKGROUND };

struct Task {
    int id;
    int priority;
    std::string name;
    TaskType type;
    std::chrono::system_clock::time_point arrival;

    bool operator<(const Task& other) const {
        // Higher priority value comes first. If equal, FCFS (earlier arrival).
        if (priority == other.priority) return arrival > other.arrival;
        return priority < other.priority;
    }
};

class OS_Scheduler {
private:
    std::priority_queue<Task> taskQueue;
    std::mutex mtx;

public:
    void schedule(int id, std::string name, int p, TaskType t) {
        std::lock_guard<std::mutex> lock(mtx);
        taskQueue.push({id, p, name, t, std::chrono::system_clock::now()});
        std::cout << "[SCHEDULER] Task '" << name << "' (ID:" << id << ") queued with Priority " << p << std::endl;
    }

    void runCycle() {
        std::lock_guard<std::mutex> lock(mtx);
        if (taskQueue.empty()) {
            std::cout << "[CPU] Idle cycle..." << std::endl;
            return;
        }

        Task current = taskQueue.top();
        taskQueue.pop();

        std::cout << "[CPU] Executing " << current.name 
                  << " [P:" << current.priority << "] Type: ";
        switch(current.type) {
            case TaskType::SYSTEM:     std::cout << "SYSTEM"; break;
            case TaskType::USER:       std::cout << "USER"; break;
            case TaskType::BACKGROUND: std::cout << "BG"; break;
        }
        std::cout << " ... DONE" << std::endl;
    }

    void status() {
        std::cout << "[SCHEDULER] Tasks pending: " << taskQueue.size() << std::endl;
    }
};

int main() {
    OS_Scheduler cpu;

    cpu.schedule(1, "Kernel Update", 10, TaskType::SYSTEM);
    cpu.schedule(2, "Web Browser", 5, TaskType::USER);
    cpu.schedule(3, "Log Rotation", 2, TaskType::BACKGROUND);
    cpu.schedule(4, "UI Refresh", 5, TaskType::USER);

    cpu.status();
    
    std::cout << "\n--- STARTING CPU CYCLES ---" << std::endl;
    for(int i=0; i<4; ++i) cpu.runCycle();
    
    return 0;
}
