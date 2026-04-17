#include <iostream>
#include <string>
#include <unordered_map>

class Account {
public:
    std::string accountNumber;
    std::string ownerName;
    double balance;

    Account() : balance(0.0) {}
    Account(std::string acc, std::string name, double bal) : accountNumber(acc), ownerName(name), balance(bal) {}
};

class Bank {
    std::unordered_map<std::string, Account> accounts;

public:
    void createAccount(std::string acc, std::string name, double initialDeposit) {
        accounts[acc] = Account(acc, name, initialDeposit);
        std::cout << "Account created for " << name << "\n";
    }

    void deposit(std::string acc, double amount) {
        if (accounts.count(acc)) {
            accounts[acc].balance += amount;
            std::cout << "Deposited " << amount << ". New balance: " << accounts[acc].balance << "\n";
        } else {
            std::cout << "Account not found.\n";
        }
    }

    void withdraw(std::string acc, double amount) {
        if (accounts.count(acc)) {
            if (accounts[acc].balance >= amount) {
                accounts[acc].balance -= amount;
                std::cout << "Withdrew " << amount << ". New balance: " << accounts[acc].balance << "\n";
            } else {
                std::cout << "Insufficient funds.\n";
            }
        } else {
            std::cout << "Account not found.\n";
        }
    }
};

int main() {
    Bank myBank;
    myBank.createAccount("1001", "Pratik Pathak", 5000.0);
    myBank.deposit("1001", 1500.0);
    myBank.withdraw("1001", 2000.0);
    myBank.withdraw("1001", 10000.0);
    return 0;
}
