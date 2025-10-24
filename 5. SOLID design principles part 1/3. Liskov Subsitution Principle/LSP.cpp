# include <iostream>
# include <vector>
using namespace std;
class DepositOnlyAccount {
public:
    virtual void deposit(double amount) = 0;
};

class WithdrawableAccount : public DepositOnlyAccount {
public:
    virtual void withdraw(double amount) = 0;
};

class SavingAccount : public WithdrawableAccount {
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

class CurrentAccount : public WithdrawableAccount {
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

class FixedDeposit : public DepositOnlyAccount {
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
}; 

class Client {
private:
    vector<DepositOnlyAccount*> acc1;
    vector<WithdrawableAccount*> acc2;
public:
    Client(vector<DepositOnlyAccount*> acc1, vector<WithdrawableAccount*> acc2) {
        this->acc1 = acc1;
        this->acc2 = acc2;
    }

    void processTransaction() {
        for(WithdrawableAccount* acc : acc2) {
            acc->deposit(10000);
            acc->withdraw(5056);
        }

        for(DepositOnlyAccount* acc : acc1) {
            acc->deposit(10000);
        }
    }
    
};

int main() {
    vector<DepositOnlyAccount*> a1;
    a1.push_back(new FixedDeposit());

    vector<WithdrawableAccount*> a2;
    a2.push_back(new SavingAccount());
    a2.push_back(new CurrentAccount());

    Client* c = new Client(a1, a2);

    c->processTransaction();
}