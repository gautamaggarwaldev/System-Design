#include <iostream>
#include <string>
#include <vector>
using namespace std;

class NPC {
public:
    string name;
    int health;
    int attack;
    int defense;

    NPC(const string& name, int health, int attack, int defense) {

        for(int i=0; i<1000000000; i++) {} //expensive
        this->name = name;
        this->health = health;
        this->attack = attack;
        this->defense = defense;

        cout << "Creating NPC '" << name << "' [HP:" << health << ", ATK:" << attack << ", DEF:" << defense << "]\n";
    }

    void describe() {
        cout << "  NPC: " << name << " | HP=" << health << " ATK=" << attack << " DEF=" << defense << "\n";
    }
};

int main() {
    NPC* alien = new NPC("Alien", 30, 5, 2);
    alien->describe();

    NPC* alien2 = new NPC("Powerful Alien", 30, 5, 5);
    alien2->describe();

    
    delete alien;
    delete alien2;
    return 0;
}