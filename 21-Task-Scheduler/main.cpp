#include <iostream>
#include <queue>
#include <vector>
#include <string>

struct Task {
    int id;
    int priority;
    std::string name;

    bool operator<(const Task& other) const {
        return priority < other.priority; // Priority queue (max-priority first)
    }
};

class Scheduler {
    std::priority_queue<Task> tasks;

public:
    void addTask(int id, std::string name, int p) {
        tasks.push({id, p, name});
        std::cout << "Task '" << name << "' scheduled.\n";
    }

    void executeNext() {
        if (!tasks.empty()) {
            Task t = tasks.top();
            std::cout << "Executing: " << t.name << " (P:" << t.priority << ")\n";
            tasks.pop();
        } else {
            std::cout << "No tasks in queue.\n";
        }
    }
};

int main() {
    Scheduler s;
    s.addTask(1, "Data Backup", 2);
    s.addTask(2, "System Update", 10);
    s.addTask(3, "UI Render", 5);

    s.executeNext();
    s.executeNext();
    return 0;
}
