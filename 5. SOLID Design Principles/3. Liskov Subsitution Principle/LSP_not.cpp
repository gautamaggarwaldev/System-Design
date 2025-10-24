# include <iostream>
# include <vector>
using namespace std;
class Account {
public:
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
};

class SavingAccount : public Account {
private: 
    double balance;
public:
    SavingAccount() {
        balance = 0;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited " << amount << " and your balance is " << balance << endl;
    }

    void withdraw(double amount) {
        if(amount <= balance) {
            balance -= amount;
            cout << "Withdraw " << amount << " and your balance is " << balance << endl;
        }
        else {
            cout << "You have not enough amount in your account" << endl;
        }
    }
};

class CurrentAccount : public Account {
private: 
    double balance;
public:
    CurrentAccount() {
        balance = 0;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited " << amount << " and your balance is " << balance << endl;
    }

    void withdraw(double amount) {
        if(amount <= balance) {
            balance -= amount;
            cout << "Withdraw " << amount << " and your balance is " << balance << endl;
        }
        else {
            cout << "You have not enough amount in your account" << endl;
        }
    }
};

class FixedDeposit : public Account {
private: 
    double balance;
public:
    FixedDeposit() {
        balance = 0;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited " << amount << " and your balance is " << balance << endl;
    }

    void withdraw(double amount) {
        throw logic_error("Withdraw is not allowed in fixed deposit account");
    }
};

class Client {
private:
    vector<Account*> accounts;
public:
    Client(vector<Account*> accounts) {
        this->accounts = accounts;
    }

    void processTransaction() {
        for(auto acc : accounts) {
            acc->deposit(10000);

            try {
                acc->withdraw(5000);
            }
            catch(const logic_error& e) {
                cout << "Exception : " << e.what() << endl;
            }
        }
    }
};
int main() {
    vector<Account*> accounts;
    accounts.push_back(new SavingAccount());
    accounts.push_back(new CurrentAccount());
    accounts.push_back(new FixedDeposit());

    Client* c = new Client(accounts);

    c->processTransaction();
}