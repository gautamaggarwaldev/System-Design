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

class SaveIntoDB {
private:
    ShoppingCart* cart;
public: 
    SaveIntoDB(ShoppingCart* cart) {
        this->cart = cart;
    }

    void SaveMongoDB() {
        cout << "Save into database successfully..." << endl;
    }
    void SaveSQLDB() {
        cout << "Save into database successfully..." << endl;
    }
    void SavePrismaDB() {
        cout << "Save into database successfully..." << endl;
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

    SaveIntoDB* db = new SaveIntoDB(sc);
    db->SaveMongoDB();
    db->SavePrismaDB();
    db->SaveSQLDB();
}
