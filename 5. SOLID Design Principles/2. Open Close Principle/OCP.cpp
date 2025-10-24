# include <iostream>
# include <vector>
using namespace std;
class Product {
public:
    string name;
    double price;
    Product(string name, double price) {
        this->name = name;
        this->price = price;
    }
};

class ShoppingCart {
private:
    vector<Product*> products;
public:
    void addProduct(Product* p) {
        products.push_back(p);
    }

    vector<Product*> getProducts() {
        return products;
    }

    double calculateTotalPrice() {
        double total = 0;
        for(auto p: products) {
            total += p->price;
        }
        return total;
    }
};

class PrintInvoice {
private:
    ShoppingCart* cart;
public:
    PrintInvoice(ShoppingCart* cart) {
        this->cart = cart;
    }
    void printInvoice() {
        cout << "Printing Invoice..." << endl;
        for(auto p : cart->getProducts()) {
            cout << p->name << " = " << p->price << endl;
        }
    }
};

//OCP

class Persistence {
private: 
    ShoppingCart* cart;
public:
    virtual void save(ShoppingCart* cart) = 0;
};

class MongoPersistence: public Persistence {
public:
    void save(ShoppingCart* cart) override {
        cout << "Save data into Monogdb..." << endl;
    }
};
class SQLPersistence: public Persistence {
public:
    void save(ShoppingCart* cart) override {
        cout << "Save data into SQL..." << endl;
    }
};
class FilePersistence: public Persistence {
public:
    void save(ShoppingCart* cart) override {
        cout << "Save data into File..." << endl;
    }
};


int main() {
    ShoppingCart* sc = new ShoppingCart();

    Product* p1 = new Product("Phone", 25000);
    Product* p2 = new Product("Laptop", 55000);
    Product* p3 = new Product("TV", 85000);
    Product* p4 = new Product("Speakers", 5000);
    Product* p5 = new Product("PS5 Pro", 50000);

    sc->addProduct(p1);
    sc->addProduct(p2);
    sc->addProduct(p3);
    sc->addProduct(p4);
    sc->addProduct(p5);

    PrintInvoice* invoice = new PrintInvoice(sc);
    invoice->printInvoice();

    Persistence* mongo = new MongoPersistence();
    Persistence* sql = new SQLPersistence();
    Persistence* file = new FilePersistence();

    mongo->save(sc);
    sql->save(sc);
    file->save(sc);

    
}