# include <iostream>
using namespace std;

class Database {
public:
    virtual void save(string data) = 0;
};

class SQLDatabase : public Database {
public:
    void save(string data) override {
        cout << "Executing SQL Query: INSERT INTO users VALUES('" << data << "');" << endl;
    }
};

class MongoDatabase : public Database {
public:
    void save(string data) override {
        cout << "Executing MongoDB Function: db.users.insert({name: '" << data << "'})" << endl;
    }
};

class User {
private:
    Database* db;
public:
    User(Database* database) {
        db = database;
    }
    void store(string user) {
        db->save(user);
    }
};
int main() {
    SQLDatabase sql;
    MongoDatabase mongo;

    User u1(&sql);
    u1.store("Garima");

    User u2(&mongo);
    u2.store("Gautam");
}