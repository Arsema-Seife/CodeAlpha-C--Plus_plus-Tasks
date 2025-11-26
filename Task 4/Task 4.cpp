#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Account {
private:
    string owner;
    double balance;

public:
    Account(string name = "", double initialBalance = 0.0) {
        owner = name;
        balance = initialBalance;
    }

    void deposit(double amount) {
        if (amount < 0) {
            cout << "Amount must be positive.\n";
            return;
        }
        balance += amount;
        cout << "Deposited: " << amount << "\n";
        cout << "Remaining balance: " << balance << "\n";
    }

    void withdraw(double amount) {
        if (amount < 0) {
            cout << "Amount must be positive.\n";
            return;
        }
        if (amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: " << amount << "\n";
            cout << "Remaining balance: " << balance << "\n";
        } else {
            cout << "Insufficient funds.\n";
        }
    }

    void transfer(Account &other, double amount) {
        if (amount < 0) {
            cout << "Amount must be positive.\n";
            return;
        }
        if (amount <= balance) {
            balance -= amount;
            other.balance += amount;
            cout << "Transferred " << amount << " to " << other.owner << "\n";
            cout << "Your remaining balance: " << balance << "\n";
        } else {
            cout << "Insufficient funds for transfer.\n";
        }
    }

    void showBalance() {
        cout << "Owner: " << owner << " | Balance: " << balance << "\n";
    }

    void saveToFile() {
        ofstream file((owner + "_account.txt").c_str());
        if (file.is_open()) {
            file << owner << endl;
            file << balance << endl;
            file.close();
        } else {
            cout << "Error saving account for " << owner << endl;
        }
    }

    void loadFromFile() {
        ifstream file((owner + "_account.txt").c_str());
        if (file.is_open()) {
            getline(file, owner);
            file >> balance;
            file.close();
        } else {
            balance = 0;
        }
    }

    string getOwner() {
        return owner;
    }
};

// Helper function to convert string to lowercase
string toLower(const string &s) {
    string result = s;
    for (size_t i = 0; i < result.length(); i++)
        if (result[i] >= 'A' && result[i] <= 'Z')
            result[i] = result[i] + ('a' - 'A');
    return result;
}

int main() {
    const int MAX_ACCOUNTS = 10;
    Account accounts[MAX_ACCOUNTS];
    int accountCount = 0;
    string choice;

    cout << "Welcome to the Bank System!\n";

    while (true) {
        cout << "\n===== MENU =====\n";
        cout << "1. Create Account\n2. Deposit\n3. Withdraw\n4. Transfer\n5. Show All Balances\n6. Exit\n";
        cout << "Enter choice: ";
        getline(cin, choice);

        if (choice == "6") {
            cout << "Exiting... Saving accounts...\n";
            for (int i = 0; i < accountCount; i++) {
                accounts[i].saveToFile();
            }
            break;
        }
        else if (choice == "1") {
            if (accountCount >= MAX_ACCOUNTS) {
                cout << "Maximum number of accounts reached.\n";
                continue;
            }
            string name;
            double balance;
            cout << "Enter account owner name: ";
            getline(cin, name);
            cout << "Enter initial balance: ";
            cin >> balance;
            cin.ignore(1000, '\n'); // clear newline
            accounts[accountCount] = Account(name, balance);
            accounts[accountCount].saveToFile();
            accountCount++;
            cout << "Account created successfully.\n";
        }
        else if (choice == "2" || choice == "3") {
            string name;
            cout << "Enter account owner name: ";
            getline(cin, name);
            int idx = -1;
            for (int i = 0; i < accountCount; i++) {
                if (toLower(accounts[i].getOwner()) == toLower(name)) {
                    idx = i;
                    break;
                }
            }
            if (idx == -1) {
                cout << "Account not found.\n";
                continue;
            }
            double amount;
            if (choice == "2") {
                cout << "Enter deposit amount: ";
                cin >> amount;
                cin.ignore(1000, '\n');
                accounts[idx].deposit(amount);
            } else {
                cout << "Enter withdrawal amount: ";
                cin >> amount;
                cin.ignore(1000, '\n');
                accounts[idx].withdraw(amount);
            }
        }
        else if (choice == "4") {
            string fromName, toName;
            double amount;
            cout << "Enter sender account owner name: ";
            getline(cin, fromName);
            cout << "Enter receiver account owner name: ";
            getline(cin, toName);
            cout << "Enter amount to transfer: ";
            cin >> amount;
            cin.ignore(1000, '\n');

            int fromIdx = -1, toIdx = -1;
            for (int i = 0; i < accountCount; i++) {
                if (toLower(accounts[i].getOwner()) == toLower(fromName)) fromIdx = i;
                if (toLower(accounts[i].getOwner()) == toLower(toName)) toIdx = i;
            }
            if (fromIdx == -1 || toIdx == -1) {
                cout << "Invalid account names.\n";
                continue;
            }
            if (fromIdx == toIdx) {
                cout << "Cannot transfer to the same account.\n";
                continue;
            }
            accounts[fromIdx].transfer(accounts[toIdx], amount);
        }
        else if (choice == "5") {
            for (int i = 0; i < accountCount; i++) {
                accounts[i].showBalance();
            }
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
