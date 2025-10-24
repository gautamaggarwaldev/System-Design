# include <iostream>
using namespace std;

// Low level Modules
class SQLDatabase {
public:
    void save (string data) {
        cout << "Executing SQL Query: INSERT INTO users VALUES('" << data << "');" << endl;
    }    
};

class MongoDatabase {
public:
    void save(string data) {
        cout << "Executing MongoDB Function: db.users.insert({name: '" << data << "'})" << endl;
    }
};

// High level Module
class User {
private:
    SQLDatabase sql;
    MongoDatabase mongo;
public: 
    void storeSQL(string user) {
        sql.save(user);
    }
    void storeMongo(string user) {
        mongo.save(user);
    }
};
int main() {
    User u;
    u.storeSQL("Garima");
    u.storeMongo("Gautam");

    return 0;
}