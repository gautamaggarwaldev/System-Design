# include <iostream>
# include <mutex>

using namespace std;
class Singleton {
private:
    static Singleton* instance;
    static mutex mtx;
    Singleton() {
        cout << "Singleton class constructor is called..." << endl;
    }

public:
    /**
     * @brief Gets the singleton instance using double-checked locking pattern
     * 
     * This method implements thread-safe lazy initialization using double-checked locking:
     * 1. First check if instance exists without locking
     * 2. Lock mutex if instance needs to be created
     * 3. Second check after acquiring lock to prevent multiple initialization
     * 
     * @return Singleton* Pointer to the singleton instance
     * @thread_safety Thread-safe due to mutex lock and double-checking
     */
    static Singleton* getInstace() {
        if(instance==nullptr) {      // first check 
            lock_guard<mutex> lock(mtx);
            if(instance==nullptr) {  // second check 
                instance = new Singleton();
            }
        }
        return instance;
    }
};

Singleton* Singleton::instance = nullptr;
mutex Singleton::mtx;

int main() {    
    Singleton* s1 = Singleton::getInstace();
    Singleton* s2 = Singleton::getInstace();
   
    if(s1==s2) cout << true;
    else cout << false;
}

