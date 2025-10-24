# include <iostream>
using namespace std;
class Shape {
public:
    virtual void area() = 0;
    virtual void volume() = 0;
};

class Rectangle : public Shape {
private:
    double length, breadth;
public:
    Rectangle(double length, double breadth) {
        this->length = length;
        this->breadth = breadth;
    }
    void area() {
        cout << "Area of rectangle : " << length * breadth << endl;
    }
    void volume() {
        throw logic_error("Not necessary");
    }
};

class Square : public Shape {
private:
    double side;
public:
    Square(double side) {
        this->side = side;
    }
    void area() {
        cout << "Area of square : " << side * side << endl;
    }
    void volume() {
        throw logic_error("Not necessary");
    }
};

class Cube : public Shape {
private:
    double side;
public: 
    Cube(double side) {
        this->side = side;
    }
    void area() {
        cout << "Area of cube : " << 6 * side * side << endl;
    }
    void volume() {
        cout << "Volume of cube : " << side * side * side << endl;
    }
};
int main() {

    Rectangle* r = new Rectangle(10,20);
    Square* s = new Square(10);
    Cube* c = new Cube(10);

    r->area();
    r->volume(); // Throw error

    s->area();
    s->volume(); // Throw error

    c->area();
    c->volume();
   
}
