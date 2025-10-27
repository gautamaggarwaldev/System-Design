# include <iostream>
using namespace std;
class Singleton {
private:
    static Singleton* instance;
    Singleton() {
        cout << "Singleton class constructor is called..." << endl;
    }
public:
    static Singleton* getInstace() {
        if(instance==nullptr) {
            instance = new Singleton();
        }
        return instance;
    }
};

Singleton* Singleton::instance = nullptr;

int main() {    
    Singleton* s1 = Singleton::getInstace();
    Singleton* s2 = Singleton::getInstace();
   
    if(s1==s2) cout << true;
    else cout << false;
}

