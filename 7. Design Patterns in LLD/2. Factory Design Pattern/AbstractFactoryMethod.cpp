# include <iostream>
using namespace std;

class Burger {
public:
    virtual void prepare() = 0;
};

class GarlicBread {
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

class BasicWheatBurger : public Burger {
public:
    void prepare() override {
        cout << "Basic Wheat Burger is contain only aalo patty" << endl;
    }
};

class StandardWheatBurger : public Burger {
public:
    void prepare() override {
        cout << "Standard Wheat Burger is contain aalo patty, two cheese slice with mayo" << endl;
    }
};

class PremiumWheatBurger : public Burger {
public:
    void prepare() override {
        cout << "Premium Wheat Burger is contain one allo patty, one paneer patty, with three cheese slice and with garlic mayo and ketchup" << endl;
    }
};

class BasicGarlicBread : public GarlicBread {
public:
    void prepare() override {
        cout << "Basic GarlicBread is contain only butter" << endl;
    }
};

class StandardGarlicBread : public GarlicBread {
public:
    void prepare() override {
        cout << "Standard GarlicBread is contain butter and mozrella cheese with oregano" << endl;
    }
};

class PremiumGarlicBread : public GarlicBread {
public:
    void prepare() override {
        cout << "Premium GarlicBread is contain butter, with cheese spread and cheese with veggi and stuffed with mushroom" << endl;
    }
};

class BasicWheatGarlicBread : public GarlicBread {
public:
    void prepare() override {
        cout << "Basic Wheat GarlicBread is contain only butter" << endl;
    }
};

class StandardWheatGarlicBread : public GarlicBread {
public:
    void prepare() override {
        cout << "Standard GarlicBread is contain butter and mozrella cheese with oregano" << endl;
    }
};

class PremiumWheatGarlicBread : public GarlicBread {
public:
    void prepare() override {
        cout << "Premium GarlicBread is contain butter, with cheese spread and cheese with veggi and stuffed with mushroom" << endl;
    }
};

class MealFactory {
public:
    virtual Burger* createburger(string type) = 0;
    virtual GarlicBread* creategarlicbread(string type) = 0;
};

class BurgerKing : public MealFactory {
public:
    Burger* createburger(string type) override {
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

    GarlicBread* creategarlicbread(string type) override {
        if(type=="basicbread") {
            return new BasicGarlicBread();
        }
        else if(type=="standardbread") {
            return new StandardGarlicBread();
        }
        else if(type=="premiumbread") {
            return new PremiumGarlicBread();
        }
        else {
            cout << "Invalid burger type.." << endl;
            return nullptr;
        }
    }
};

class BurgerSingh : public MealFactory {
public:
    Burger* createburger(string type) override {
        if(type=="basicwheat") {
            return new BasicWheatBurger();
        }
        else if(type=="standardwheat") {
            return new StandardWheatBurger();
        }
        else if(type=="premiumwheat") {
            return new PremiumWheatBurger();
        }
        else {
            cout << "Invalid burger type.." << endl;
            return nullptr;
        }
    }

    GarlicBread* creategarlicbread(string type) override {
        if(type=="basicwheatbread") {
            return new BasicWheatGarlicBread();
        }
        else if(type=="standardwheatbread") {
            return new StandardWheatGarlicBread();
        }
        else if(type=="premiumwheatbread") {
            return new PremiumWheatGarlicBread();
        }
        else {
            cout << "Invalid burger type.." << endl;
            return nullptr;
        }
    }
};

int main() {
    MealFactory* bf1 = new BurgerSingh();
    Burger* b1 = bf1->createburger("standardwheat");
    GarlicBread* gb1 = bf1->creategarlicbread("premiumwheatbread");
    b1->prepare();
    gb1->prepare();

    cout << "``````````````````````````" << endl;
    
    MealFactory* bf2 = new BurgerKing();
    Burger* b2 = bf2->createburger("premium");
    GarlicBread* gb2 = bf2->creategarlicbread("basicbread");
    b2->prepare();
    gb2->prepare();
}