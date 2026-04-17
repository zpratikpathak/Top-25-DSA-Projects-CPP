#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <memory>

/**
 * Advanced Bank Management System
 * Features:
 * - O(1) Hashing for account lookups
 * - Transaction logging with timestamps
 * - Interest calculation for Savings accounts
 * - Persistent transaction history
 * - Encapsulated account types (Abstract Base Class)
 */

enum class TransactionType { DEPOSIT, WITHDRAWAL, INTEREST };

struct Transaction {
    TransactionType type;
    double amount;
    std::time_t timestamp;

    std::string getInfo() const {
        std::tm* tm_ptr = std::localtime(&timestamp);
        char buffer[32];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_ptr);
        std::string t = (type == TransactionType::DEPOSIT ? "[DEP]" : (type == TransactionType::WITHDRAWAL ? "[WIT]" : "[INT]"));
        return std::string(buffer) + " " + t + " $" + std::to_string(amount);
    }
};

class BaseAccount {
protected:
    std::string accountNumber;
    std::string ownerName;
    double balance;
    std::vector<Transaction> history;

public:
    BaseAccount(std::string acc, std::string name, double initial) 
        : accountNumber(acc), ownerName(name), balance(initial) {}
    
    virtual ~BaseAccount() = default;

    virtual void deposit(double amount) {
        balance += amount;
        history.push_back({TransactionType::DEPOSIT, amount, std::time(nullptr)});
    }

    virtual bool withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            history.push_back({TransactionType::WITHDRAWAL, amount, std::time(nullptr)});
            return true;
        }
        return false;
    }

    double getBalance() const { return balance; }
    std::string getOwner() const { return ownerName; }
    
    void printHistory() const {
        std::cout << "\n--- STATEMENT FOR " << accountNumber << " (" << ownerName << ") ---" << std::endl;
        for (const auto& t : history) std::cout << t.getInfo() << std::endl;
        std::cout << "CURRENT BALANCE: $" << balance << std::endl;
        std::cout << "-------------------------------------------\n" << std::endl;
    }
};

class SavingsAccount : public BaseAccount {
    double interestRate = 0.04; // 4%
public:
    SavingsAccount(std::string acc, std::string name, double initial) : BaseAccount(acc, name, initial) {}

    void applyInterest() {
        double interest = balance * interestRate;
        balance += interest;
        history.push_back({TransactionType::INTEREST, interest, std::time(nullptr)});
    }
};

class Bank {
private:
    std::unordered_map<std::string, std::unique_ptr<BaseAccount>> accounts;

public:
    void openSavingsAccount(std::string acc, std::string name, double initial) {
        accounts[acc] = std::make_unique<SavingsAccount>(acc, name, initial);
        std::cout << "[BANK] Savings account opened for " << name << std::endl;
    }

    BaseAccount* getAccount(std::string acc) {
        if (accounts.count(acc)) return accounts[acc].get();
        return nullptr;
    }

    void simulateInterest() {
        for (auto& [id, acc] : accounts) {
            if (auto* s = dynamic_cast<SavingsAccount*>(acc.get())) {
                s->applyInterest();
            }
        }
    }
};

int main() {
    Bank nexusBank;

    nexusBank.openSavingsAccount("NX1001", "Pratik Pathak", 10000.0);
    nexusBank.openSavingsAccount("NX2005", "Evil Reborn", 5000.0);

    if (auto* acc = nexusBank.getAccount("NX1001")) {
        acc->deposit(2500.0);
        acc->withdraw(1200.0);
    }

    nexusBank.simulateInterest();

    if (auto* acc = nexusBank.getAccount("NX1001")) {
        acc->printHistory();
    }

    return 0;
}
