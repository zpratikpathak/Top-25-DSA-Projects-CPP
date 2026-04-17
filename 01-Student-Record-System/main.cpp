#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <memory>

/**
 * Advanced Student Record System
 * Features:
 * - Persistent storage with file I/O
 * - Chained Hashing for O(1) average lookup
 * - Dynamic resizing and rehashing
 * - GPA Statistics and Advanced Querying
 */

struct Student {
    int id;
    std::string name;
    std::string department;
    float gpa;

    void display() const {
        std::cout << std::left << std::setw(10) << id 
                  << std::setw(20) << name 
                  << std::setw(20) << department 
                  << std::fixed << std::setprecision(2) << gpa << std::endl;
    }
};

class StudentDatabase {
private:
    static constexpr float MAX_LOAD_FACTOR = 0.75;
    size_t tableSize;
    size_t studentCount;
    std::vector<std::vector<Student>> table;

    size_t hashFunction(int id) const {
        return id % tableSize;
    }

    void rehash() {
        std::cout << "[SYSTEM] Capacity threshold reached. Rehashing database..." << std::endl;
        auto oldTable = std::move(table);
        tableSize *= 2;
        table.assign(tableSize, std::vector<Student>());
        studentCount = 0;

        for (const auto& bucket : oldTable) {
            for (const auto& student : bucket) {
                insert(student, false);
            }
        }
    }

public:
    StudentDatabase(size_t initialSize = 11) : tableSize(initialSize), studentCount(0) {
        table.resize(tableSize);
    }

    void insert(const Student& s, bool verbose = true) {
        if ((float)(studentCount + 1) / tableSize > MAX_LOAD_FACTOR) {
            rehash();
        }

        size_t index = hashFunction(s.id);
        // Check for duplicates
        for (auto& student : table[index]) {
            if (student.id == s.id) {
                student = s; // Update existing
                if (verbose) std::cout << "[SUCCESS] Record for ID " << s.id << " updated." << std::endl;
                return;
            }
        }

        table[index].push_back(s);
        studentCount++;
        if (verbose) std::cout << "[SUCCESS] Added student: " << s.name << std::endl;
    }

    Student* find(int id) {
        size_t index = hashFunction(id);
        for (auto& s : table[index]) {
            if (s.id == id) return &s;
        }
        return nullptr;
    }

    bool remove(int id) {
        size_t index = hashFunction(id);
        auto& bucket = table[index];
        auto it = std::remove_if(bucket.begin(), bucket.end(), [id](const Student& s) { return s.id == id; });
        if (it != bucket.end()) {
            bucket.erase(it, bucket.end());
            studentCount--;
            return true;
        }
        return false;
    }

    void displayStatistics() const {
        if (studentCount == 0) return;
        float sum = 0;
        for (const auto& bucket : table) {
            for (const auto& s : bucket) sum += s.gpa;
        }
        std::cout << "\n--- DATABASE STATISTICS ---" << std::endl;
        std::cout << "Total Students: " << studentCount << std::endl;
        std::cout << "Average GPA:    " << (sum / studentCount) << std::endl;
        std::cout << "Load Factor:    " << (float)studentCount / tableSize << std::endl;
        std::cout << "---------------------------\n" << std::endl;
    }

    void listAll() const {
        std::cout << std::left << std::setw(10) << "ID" 
                  << std::setw(20) << "NAME" 
                  << std::setw(20) << "DEPT" 
                  << "GPA" << std::endl;
        std::cout << std::string(60, '-') << std::endl;
        for (const auto& bucket : table) {
            for (const auto& s : bucket) s.display();
        }
    }

    void saveToFile(const std::string& filename) {
        std::ofstream outFile(filename);
        for (const auto& bucket : table) {
            for (const auto& s : bucket) {
                outFile << s.id << "," << s.name << "," << s.department << "," << s.gpa << "\n";
            }
        }
        std::cout << "[SYSTEM] Database saved to " << filename << std::endl;
    }
};

int main() {
    StudentDatabase db;

    // Simulate high-volume insertions
    db.insert({1001, "Pratik Pathak", "Computer Science", 3.95});
    db.insert({1052, "John Doe", "Mathematics", 3.40});
    db.insert({2105, "Alice Smith", "Physics", 3.85});
    db.insert({3002, "Evil Reborn", "Cyber Security", 4.00});
    db.insert({1001, "Pratik P.", "AI & Robotics", 4.00}); // Update duplicate

    db.listAll();
    db.displayStatistics();

    int searchId = 3002;
    std::cout << "Searching for ID " << searchId << "..." << std::endl;
    if (auto* s = db.find(searchId)) {
        std::cout << "FOUND: ";
        s->display();
    } else {
        std::cout << "NOT FOUND." << std::endl;
    }

    db.saveToFile("students.csv");

    return 0;
}
