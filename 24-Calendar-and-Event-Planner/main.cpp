#include <iostream>
#include <map>
#include <string>

class EventPlanner {
    std::map<std::string, std::string> events; // Date (YYYY-MM-DD) -> Description

public:
    void addEvent(std::string date, std::string desc) {
        events[date] = desc;
        std::cout << "Event added for " << date << "\n";
    }

    void showCalendar() {
        std::cout << "\n--- Calendar ---\n";
        for (auto const& [date, desc] : events) {
            std::cout << date << ": " << desc << "\n";
        }
    }
};

int main() {
    EventPlanner myPlan;
    myPlan.addEvent("2026-04-17", "DSA Repository Completion");
    myPlan.addEvent("2026-04-20", "Sprint Review");
    myPlan.addEvent("2026-04-15", "Market Intelligence Setup");

    myPlan.showCalendar();
    return 0;
}
