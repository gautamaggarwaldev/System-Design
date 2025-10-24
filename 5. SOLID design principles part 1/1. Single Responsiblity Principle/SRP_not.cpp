#include <iostream>
#include <vector>
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
        cout << "Product added..." << endl;
    }

    vector<Product*> getProducts() {
        cout << "Fetching products..." << endl;
        return products;
    }

    double calculateTotalPrice() {
        double total = 0;
        for(auto p: products) {
            total += p->price;
        }
        return total;
    }

    void printInvoice() {
        cout << "Invoice is Printing...." << endl;
        for(auto p : products) {
            cout << p->name << " : " << p->price << endl;
        }
        cout << "Thank you!" << endl;
    }

    void saveToDB() {
        cout << "Data save in database successfully..." << endl;
    }
};
int main() {
    Product* p1 = new Product("Phone", 25000);
    Product* p2 = new Product("Laptop", 55000);
    Product* p3 = new Product("TV", 85000);
    Product* p4 = new Product("Speakers", 5000);
    Product* p5 = new Product("PS5 Pro", 50000);


    ShoppingCart* sc = new ShoppingCart();

    sc->addProduct(p1);
    sc->addProduct(p2);
    sc->addProduct(p3);
    sc->addProduct(p4);
    sc->addProduct(p5);

    cout << "Total Price : " << sc->calculateTotalPrice() << endl;
    sc->printInvoice();

    vector<Product*> allProducts = sc->getProducts();
    for (auto p : allProducts) {
        cout << p->name << " : " << p->price << endl;
    }
    
    sc->saveToDB();
}