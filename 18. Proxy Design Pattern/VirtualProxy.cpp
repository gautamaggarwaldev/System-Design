# include <iostream>
using namespace std;

class IImage {
public:
    virtual void display() = 0;
    ~IImage() {};
};

class RealImage : public IImage {
private:
    string filename;
public:
    RealImage(string filename) {
        this->filename = filename;

        cout << "The image is loading on disk: " << filename << endl;
    }

    void display() override {
        cout << "The image is displayed successfully" << endl;
    }
};

class ImageProxy : public IImage {
private:
    string filename;
    RealImage* image;
public:
    ImageProxy(string filename) {
        this->filename = filename;
        image = nullptr;
    }

    void display() override {
        if(image==nullptr) {
            image = new RealImage(filename);
        }
        image->display();
    }
};


int main() {

    IImage* im = new ImageProxy("display.png");
    im->display();
    delete im;
}
