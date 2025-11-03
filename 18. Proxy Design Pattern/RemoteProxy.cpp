# include <iostream>
using namespace std;

class IDataService {
public:
    virtual string fetchData() = 0;
    virtual ~IDataService() {};
};

class RealDataService : public IDataService {
public:
    RealDataService() {
        cout << "[RealDataService] Initialized (simulating remote setup)\n";
    }
    string fetchData() override {
        return "[RealDataService] Data from server";
    }
};

class DataServiceProxy : public IDataService {
private:
    RealDataService* realservice = nullptr;
public:
    DataServiceProxy() {
        realservice = new RealDataService();
    }

    string fetchData() override {
        cout << "[DataServiceProxy] Connecting to remote service...\n";
        return realservice->fetchData();
    }
};

int main() {
    IDataService* dataservice = new DataServiceProxy();
    dataservice->fetchData();
}
