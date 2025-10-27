# include <iostream>
using namespace std;
class Singleton {
public:
    Singleton() {
        cout << "Singleton class constructor is called..." << endl;
    }
};
int main() {    
    Singleton* s1 = new Singleton();
    Singleton* s2 = new Singleton();
   
    if(s1==s2) cout << true;
    else cout << false;
}
