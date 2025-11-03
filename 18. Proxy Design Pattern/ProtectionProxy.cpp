# include <iostream>
using namespace std;

class IDocumentReader {
public:
    virtual void unlockPdf(string filePath, string password) = 0;
    virtual ~IDocumentReader() {};
};

class RealDocument : public IDocumentReader {
public:
    void unlockPdf(string filePath, string password) override {
        cout << "[RealDocumentReader] Unlocking PDF at: " << filePath << "\n";
        cout << "[RealDocumentReader] PDF unlocked successfully with password: " << password << "\n";
        cout << "[RealDocumentReader] Displaying PDF content...\n";
    }
};

class User {
public:
    string name;
    bool isPremiumMember;
    User(string name, bool isPremiumMember) {
        this->name = name;
        this->isPremiumMember = isPremiumMember;
    }
};

class DocumentProxy : public IDocumentReader {
private:
    User* user;
    RealDocument* realReader;
public:
    DocumentProxy(User* user) {
        this->user = user;
        realReader = new RealDocument();
    }

    void unlockPdf(string filePath, string password) override {
        if(user->isPremiumMember==false) {
            cout << "[DocumentProxy] Access denied. Only premium members can unlock PDFs.\n";
            return;
        }
        realReader->unlockPdf(filePath, password);
    }

    ~DocumentProxy() {
        delete realReader;
    }
};

int main() {
    User* user1 = new User("Garima", false);
    User* user2 = new User("Gautam", true);  

    cout << "== Garima (Non-Premium) tries to unlock PDF ==\n";
    IDocumentReader* docReader = new DocumentProxy(user1);
    docReader->unlockPdf("protected_document.pdf", "secret123");
    delete docReader;

    cout << "\n== Gautam (Premium) unlocks PDF ==\n";
    docReader = new DocumentProxy(user2);
    docReader->unlockPdf("protected_document.pdf", "secret123");
    delete docReader;
}