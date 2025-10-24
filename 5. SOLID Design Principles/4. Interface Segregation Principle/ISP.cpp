# include <iostream>
using namespace std;

class TwoDimensionalShape {
public:
    virtual void area() = 0;
};

class ThreeDimensionalShape {
public:
    virtual void area() = 0;
    virtual void volume() = 0;
};

class Rectangle : public TwoDimensionalShape {
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
};

class Square : public TwoDimensionalShape {
private:
    double side;
public:
    Square(double side) {
        this->side = side;
    }
    void area() {
        cout << "Area of square : " << side * side << endl;
    }
};

class Cube : public ThreeDimensionalShape {
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

    s->area();

    c->area();
    c->volume();
    
}