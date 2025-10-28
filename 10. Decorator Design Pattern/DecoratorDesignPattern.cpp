# include <iostream>
using namespace std;

class Character {
public:
    virtual string getAbilities() = 0;
    virtual ~Character() {};
};

class Mario : public Character {
public:
    Mario() {};

    string getAbilities() override {
        return "Mario with basic power";
    }
};

class DecoratorCharacter : public Character{
protected:
    Character* ch;
public:
    DecoratorCharacter(Character* ch) {
        this->ch = ch;
    }
};


class HeightUpDecorator : public DecoratorCharacter {
public:
    HeightUpDecorator(Character* ch) : DecoratorCharacter(ch) {};

    string getAbilities() override {
        return ch->getAbilities() + " with Height increase power";
    }
};

class GunPowerDecorator : public DecoratorCharacter {
public:
    GunPowerDecorator(Character* ch) : DecoratorCharacter(ch) {};

    string getAbilities() override {
        return ch->getAbilities() + " with gun power";
    }
};

class StarDecorator : public DecoratorCharacter {
public:
    StarDecorator(Character* ch) : DecoratorCharacter(ch) {};

    string getAbilities() override {
        return ch->getAbilities() + " with Star power (Limited Time)";
    }

    ~StarDecorator() {
        cout << "Destroying this star power...";
    }
};

int main() {

    Character* mario = new Mario();
    cout << mario->getAbilities() << endl;
    
    mario = new HeightUpDecorator(mario);
    cout << mario->getAbilities() << endl;

    mario = new GunPowerDecorator(mario);
    cout << mario->getAbilities() << endl;

    mario = new StarDecorator(mario);
    cout << mario->getAbilities() << endl;

    delete mario;
}
