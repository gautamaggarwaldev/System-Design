# include <iostream>
# include <vector>
#include <stdexcept>

using namespace std;

class FileSystem {
public:
    virtual void ls(int indent = 0) = 0;
    virtual void openAll(int indent = 0) = 0;
    virtual int getSize() = 0;
    virtual string getName() = 0;
    virtual FileSystem* cd(const string& name) = 0;
    virtual bool isFolder() = 0;
};

class File : public FileSystem {
private:
    string name;
    int size;
public:
    File(string name, int size) {
        this->name = name;
        this->size = size;
    }

    void ls(int indent = 0) override {
        cout << string(indent, ' ') << name << "\n";
    }

    void openAll(int indent = 0) override {
        cout << string(indent, ' ') << name << "\n";
    }

    int getSize() override {
        return size;
    }

    FileSystem* cd(const string&) override {
        return nullptr;
    }

    string getName() override {
        return name;
    }

    bool isFolder() override {
        return false;
    }
};


class Folder : public FileSystem {
private:
    string name;
    vector<FileSystem*> children;
public:
    Folder(const string& n) {
        name = n;
    }
    ~Folder() {
        for (auto c : children) delete c;
    }

    void add(FileSystem* f) {
        children.push_back(f);
    }

    void ls(int indent = 0) override {
        for(auto child : children) {
            if(child->isFolder()) {
                cout <<string(indent, ' ') << "+ " << child->getName() << "\n";
            }
            else {
                cout <<string(indent, ' ') << child->getName() << "\n";
            }
        }
    }

    void openAll(int indent = 0) override {
        cout << string(indent, ' ') << "+ " << name << "\n";
        for(auto child : children) {
            child->openAll(indent + 4);
        }
    }

    int getSize() override {
        int total = 0;
        for(auto child : children) {
            total += child->getSize();
        }
        return total;
    }

    FileSystem* cd(const string& target) override {
        for (auto child : children) {
            if (child->isFolder() && child->getName() == target) {
                return child;
            }
        }
        return nullptr;
    }

    string getName() override {
        return name;
    }

    bool isFolder() override {
        return true;
    }

};

int main() {

    Folder* root = new Folder("root");
    root->add(new File("file1.txt", 1));
    root->add(new File("file2.txt", 1));

    Folder* docs = new Folder("docs");
    docs->add(new File("resume.pdf", 1));
    docs->add(new File("notes.txt", 1));
    root->add(docs);

    Folder* images = new Folder("images");
    images->add(new File("photo.jpg", 1));
    root->add(images);

    root->ls();

    docs->ls();

    root->openAll();

    FileSystem* cwd = root->cd("docs");
    if (cwd != nullptr) {
        cwd->ls();
    } else {
        cout << "\n Could not cd into docs \n";
    }

    cout << root->getSize();

    delete root;   
}
