# include <iostream>
using namespace std;
class MoneyHandler {
protected:
    MoneyHandler *nextHandler;
public:
    MoneyHandler() {
        this->nextHandler = nullptr;
    }

    void setNextHandler(MoneyHandler* next) {
        nextHandler = next;
    }

    virtual void dispense(int amount) = 0;
};

class ThousandHandler : public MoneyHandler {
private:
    int numNotes;
public:
    ThousandHandler(int numNotes) {
        this->numNotes = numNotes;
    }

    void dispense(int amount) override {
        int notesNeeded = amount / 1000;

        if(notesNeeded > numNotes) {
            notesNeeded = numNotes;
            numNotes = 0;
        }
        else {
            numNotes -= notesNeeded;
        }

        if(notesNeeded > 0) cout << "Dispensing " << notesNeeded << " x $1000 notes.\n";

        int remainingAmount = amount - (notesNeeded * 1000);
        if(remainingAmount > 0) {
            if(nextHandler != nullptr) nextHandler->dispense(remainingAmount);
            else {
                cout << "Remaining amount of " << remainingAmount << " cannot be fulfilled (Insufficinet fund in ATM)\n";
            }
        }
    }
};
class FiveHundredHandler : public MoneyHandler {
private:
    int numNotes;
public:
    FiveHundredHandler(int numNotes) {
        this->numNotes = numNotes;
    }

    void dispense(int amount) override {
        int notesNeeded = amount / 500;

        if(notesNeeded > numNotes) {
            notesNeeded = numNotes;
            numNotes = 0;
        }
        else {
            numNotes -= notesNeeded;
        }

        if(notesNeeded > 0) cout << "Dispensing " << notesNeeded << " x $500 notes.\n";

        int remainingAmount = amount - (notesNeeded * 500);
        if(remainingAmount > 0) {
            if(nextHandler != nullptr) nextHandler->dispense(remainingAmount);
            else {
                cout << "Remaining amount of " << remainingAmount << " cannot be fulfilled (Insufficinet fund in ATM)\n";
            }
        }
    }
};
class HundredHandler : public MoneyHandler {
private:
    int numNotes;
public:
    HundredHandler(int numNotes) {
        this->numNotes = numNotes;
    }

    void dispense(int amount) override {
        int notesNeeded = amount / 100;

        if(notesNeeded > numNotes) {
            notesNeeded = numNotes;
            numNotes = 0;
        }
        else {
            numNotes -= notesNeeded;
        }

        if(notesNeeded > 0) cout << "Dispensing " << notesNeeded << " x $100 notes.\n";

        int remainingAmount = amount - (notesNeeded * 100);
        if(remainingAmount > 0) {
            if(nextHandler != nullptr) nextHandler->dispense(remainingAmount);
            else {
                cout << "Remaining amount of " << remainingAmount << " cannot be fulfilled (Insufficinet fund in ATM)\n";
            }
        }
    }
};
class FiftyHandler : public MoneyHandler {
private:
    int numNotes;
public:
    FiftyHandler(int numNotes) {
        this->numNotes = numNotes;
    }

    void dispense(int amount) override {
        int notesNeeded = amount / 50;

        if(notesNeeded > numNotes) {
            notesNeeded = numNotes;
            numNotes = 0;
        }
        else {
            numNotes -= notesNeeded;
        }

        if(notesNeeded > 0) cout << "Dispensing " << notesNeeded << " x $50 notes.\n";

        int remainingAmount = amount - (notesNeeded * 50);
        if(remainingAmount > 0) {
            if(nextHandler != nullptr) nextHandler->dispense(remainingAmount);
            else {
                cout << "Remaining amount of " << remainingAmount << " cannot be fulfilled (Insufficinet fund in ATM)\n";
            }
        }
    }
};
int main() {

    MoneyHandler* thousandHandler = new ThousandHandler(3);
    MoneyHandler* fiveHundredHandler = new FiveHundredHandler(5);
    MoneyHandler* hundredHandler= new HundredHandler(20);
    MoneyHandler* fiftyHandler= new FiftyHandler(10);

    thousandHandler->setNextHandler(fiveHundredHandler);
    fiveHundredHandler->setNextHandler(hundredHandler);
    hundredHandler->setNextHandler(fiftyHandler);

    int amountToWithdraw = 5250;

    cout << "\nDispensing amount: $" << amountToWithdraw << endl;
    thousandHandler->dispense(amountToWithdraw);

   
}
