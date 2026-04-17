#include <iostream>
#include <string>
#include <vector>
#include <list>

class Student {
public:
    int id;
    std::string name;
    float gpa;

    Student(int i, std::string n, float g) : id(i), name(n), gpa(g) {}
};

class RecordSystem {
    int capacity = 100;
    std::vector<std::list<Student>> table;

    int hashFunction(int id) {
        return id % capacity;
    }

public:
    RecordSystem() : table(capacity) {}

    void insert(int id, std::string name, float gpa) {
        int index = hashFunction(id);
        table[index].emplace_back(id, name, gpa);
        std::cout << "Student " << name << " added successfully.\n";
    }

    void find(int id) {
        int index = hashFunction(id);
        for (const auto& s : table[index]) {
            if (s.id == id) {
                std::cout << "Found: " << s.name << " (GPA: " << s.gpa << ")\n";
                return;
            }
        }
        std::cout << "Student ID " << id << " not found.\n";
    }

    void displayAll() {
        std::cout << "\n--- All Records ---\n";
        for (int i = 0; i < capacity; ++i) {
            for (const auto& s : table[i]) {
                std::cout << "ID: " << s.id << " | Name: " << s.name << " | GPA: " << s.gpa << "\n";
            }
        }
    }
};

int main() {
    RecordSystem rs;
    rs.insert(101, "Pratik", 3.9);
    rs.insert(102, "Evil", 4.0);
    rs.insert(201, "Alice", 3.7);

    rs.find(101);
    rs.find(999);
    
    rs.displayAll();
    return 0;
}
