# include <iostream>
using namespace std;

class Engine {
public:
    virtual void start() = 0;
    virtual ~Engine() {};
};

class PetrolEngine : public Engine {
public:
    void start() override {
        cout << "Petrol Engine Start" << endl;
    }
};

class DieselEngine : public Engine {
public:
    void start() override {
        cout << "Diesel Engine Start" << endl;
    }
};

class ElectricEngine : public Engine {
public:
    void start() override {
        cout << "Electric Engine Start" << endl;
    }
};

class Car {
protected:
    Engine* engine;
public:
    Car(Engine* engine) {
        this->engine = engine;
    }
    virtual void drive() = 0;
};

class Sedan : public Car {
public:
    Sedan(Engine* e) : Car(e) {}

    void drive() override {
        engine->start();
        cout << "Sedan car drive..." << endl;
    }
};

class SUV : public Car {
public:
    SUV(Engine* e) : Car(e) {}

    void drive() override {
        engine->start();
        cout << "SUV car drive..." << endl;
    }
};
class Haybatch : public Car {
public:
    Haybatch(Engine* e) : Car(e) {}

    void drive() override {
        engine->start();
        cout << "Haybatch car drive..." << endl;
    }
};

int main() {

    Engine* engine1 = new PetrolEngine();
    Engine* engine2 = new DieselEngine();
    Engine* engine3 = new ElectricEngine();

    Car* car1 = new Sedan(engine1);
    Car* car2 = new SUV(engine2);
    Car* car3 = new Haybatch(engine3);

    car1->drive();
    car2->drive();
    car3->drive();

    delete car1;
    delete car2;
    delete car3;
    delete engine1;
    delete engine2;
    delete engine3;
   
}