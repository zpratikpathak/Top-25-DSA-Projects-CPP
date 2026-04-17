#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

/**
 * Advanced Calendar and Event Planner
 * Features:
 * - Red-Black Tree implementation (via std::map) for O(log N) operations
 * - Multi-event support per time slot
 * - Search by date ranges
 * - Conflict detection and priority metrics
 */

struct Event {
    std::string title;
    std::string time;
    int priority; // 1-5
    std::string category;

    bool operator<(const Event& other) const {
        if (time == other.time) return priority > other.priority;
        return time < other.time;
    }
};

class EventPlanner {
private:
    std::map<std::string, std::vector<Event>> calendar; // Date -> List of Events

public:
    void addEvent(const std::string& date, const Event& e) {
        calendar[date].push_back(e);
        std::sort(calendar[date].begin(), calendar[date].end());
        std::cout << "[SUCCESS] Scheduled: " << e.title << " on " << date << std::endl;
    }

    void showRange(const std::string& start, const std::string& end) {
        auto itStart = calendar.lower_bound(start);
        auto itEnd = calendar.upper_bound(end);

        std::cout << "\n--- EVENTS FROM " << start << " TO " << end << " ---" << std::endl;
        for (auto it = itStart; it != itEnd; ++it) {
            std::cout << "\nDATE: " << it->first << std::endl;
            for (const auto& e : it->second) {
                std::cout << " [" << e.time << "] (P" << e.priority << ") " 
                          << std::left << std::setw(25) << e.title 
                          << " Category: " << e.category << std::endl;
            }
        }
        std::cout << "-------------------------------------------\n" << std::endl;
    }

    void checkConflicts(const std::string& date) {
        if (!calendar.count(date)) return;
        auto const& events = calendar[date];
        for (size_t i = 0; i < events.size() - 1; ++i) {
            if (events[i].time == events[i+1].time) {
                std::cout << "[CONFLICT] Multiple events at " << events[i].time << " on " << date << std::endl;
            }
        }
    }
};

int main() {
    EventPlanner planner;

    planner.addEvent("2026-04-17", {"Code Review", "09:00", 4, "Work"});
    planner.addEvent("2026-04-17", {"Team Sync", "11:00", 3, "Work"});
    planner.addEvent("2026-04-17", {"Deep Work", "11:00", 5, "Personal"}); // Conflict
    planner.addEvent("2026-04-18", {"Client Meeting", "14:00", 4, "Work"});
    planner.addEvent("2026-04-20", {"Deployment", "02:00", 5, "Release"});

    planner.checkConflicts("2026-04-17");
    planner.showRange("2026-04-17", "2026-04-19");

    return 0;
}
