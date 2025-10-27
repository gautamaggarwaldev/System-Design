# include <iostream>
using namespace std;

class Burger {
public:
    virtual void prepare() = 0;
};

class BasicBurger : public Burger {
public:
    void prepare() override {
        cout << "Basic Burger is contain only aalo patty" << endl;
    }
};

class StandardBurger : public Burger {
public:
    void prepare() override {
        cout << "Standard Burger is contain aalo patty, two cheese slice with mayo" << endl;
    }
};

class PremiumBurger : public Burger {
public:
    void prepare() override {
        cout << "Premium Burger is contain one allo patty, one paneer patty, with three cheese slice and with garlic mayo and ketchup" << endl;
    }
};

class BurgerFactory {
public:
    Burger* createburger(string type) {
        if(type=="basic") {
            return new BasicBurger();
        }
        else if(type=="standard") {
            return new StandardBurger();
        }
        else if(type=="premium") {
            return new PremiumBurger();
        }
        else {
            cout << "Invalid burger type.." << endl;
            return nullptr;
        }
    }
};

int main() {
    BurgerFactory* bf = new BurgerFactory();
    Burger* b = bf->createburger("premium");
    b->prepare();
}