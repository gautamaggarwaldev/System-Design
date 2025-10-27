# include <iostream>
using namespace std;

class Walkable {
public:
    virtual void walk() = 0;
    virtual ~Walkable() {};
};

class NormalWalk : public Walkable {
public:
    void walk() override {
        cout << "Normal walk initialised..." << endl;
    }
};

class NoWalk : public Walkable {
public:
    void walk() override {
        cout << "No walk functionality implemented..." << endl;
    }
};

class Talkable {
public:
    virtual void talk() = 0;
    virtual ~Talkable() {};
};

class NormalTalk : public Talkable {
public:
    void talk() override {
        cout << "Normal talk initialised..." << endl;
    }
};

class NoTalk : public Talkable {
public:
    void talk() override {
        cout << "No talk functionality implemented..." << endl;
    }
};

class Flyable {
public:
    virtual void fly() = 0;
    virtual ~Flyable() {};
};

class NormalFly : public Flyable {
public:
    void fly() override {
        cout << "Normal fly initialised..." << endl;
    }
};

class NoFly : public Flyable {
public:
    void fly() override {
        cout << "No fly functionality implemented..." << endl;
    }
};


class Robot {
protected:
    Walkable* walkbehaviour;
    Talkable* talkbehaviour;
    Flyable* flybehaviour;
public:
    Robot(Walkable* w, Talkable* t, Flyable* f) {
        this->walkbehaviour = w;
        this->talkbehaviour = t;
        this->flybehaviour = f;
    }

    void walk() {
        walkbehaviour->walk();
    }

    void talk() {
        talkbehaviour->talk();
    }

    void fly() {
        flybehaviour->fly();
    }

    virtual void projection() = 0;
};

class CompanionRobot : public Robot {
public:
    CompanionRobot(Walkable* w, Talkable* t, Flyable* f) : Robot(w,t,f) {}
    void projection() override {
        cout << "Friendly robot" << endl;
    }
};

class WorkerRobot : public Robot {
public:
    WorkerRobot(Walkable* w, Talkable* t, Flyable* f) : Robot(w,t,f) {}
    void projection() override {
        cout << "Wroker robot" << endl;
    }
};

int main() {

    Robot* r1 = new CompanionRobot(new NormalWalk(), new NormalTalk(), new NoFly());
    r1->walk();
    r1->talk();
    r1->fly();
    r1->projection();

    cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;

    Robot* r2 = new WorkerRobot(new NoWalk(), new NormalTalk(), new NormalFly());
    r2->walk();
    r2->talk();
    r2->fly();
    r2->projection();
   
}