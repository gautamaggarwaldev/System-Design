# include <iostream>
# include <vector>
using namespace std;

class User {
private:
    string name;
    vector<User*> users;
    vector<string> mutedUsers;
public:
    User(const string& n) {
        name= n;
    }

    void addPeer(User* u) {
        users.push_back(u);
    }

    void mute(const string& userToMute) {
        mutedUsers.push_back(userToMute);
    }

    bool isMuted(string userName) {
        for(auto name : mutedUsers) {
            if(name == userName) {
                return true;
            }
        }
        return false;
    }

    void receive(const string& from, const string& msg) {
        cout << "    " << name << " got from " << from << ": " << msg << endl;
    }

    void send(const string& message) {
        cout << "[" << name << " broadcasts]: " << message << endl;
        for(User* peer : users) {
            if(!peer->isMuted(name)) {
                peer->receive(name, message);
            }
        }
    }

    void sendTo(User* target, const string& msg) { //private message
        cout << "[" << name << "->" << target->name << "]: " << msg << endl;
        if(!target->isMuted(name)) {
            target->receive(name, msg);
        }
    }
};

int main() {
    User* user1 = new User("Garima");
    User* user2 = new User("Neha");
    User* user3 = new User("GG");

    user1->addPeer(user2);   
    user2->addPeer(user1);

    user1->addPeer(user3);   
    user3->addPeer(user1);

    user2->addPeer(user3); 
    user3->addPeer(user2);

    user1->mute("GG");

    // broadcast
    user1->send("Hello everyone!");

    // private
    user1->sendTo(user3, "Hey GG!");

    // cleanup
    delete user1;
    delete user2;
    delete user3;
}
