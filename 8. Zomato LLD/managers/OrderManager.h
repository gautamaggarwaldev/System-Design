#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include<vector>
#include<string>
#include "../models/Order.h"
using namespace std;

class OrderManager {
private:
    vector<Order*> orders;
    static OrderManager* instance;

    OrderManager() {}

public:
    static OrderManager* getInstance() { // use singleton design pattern
        if(!instance) {
            instance = new OrderManager();
        }
        return instance;
    }

    void addOrder(Order* order) {
        orders.push_back(order);
    }

    void listOrders() {
        cout << "\n--- All Orders ---" << endl;
        for (auto order : orders) {
            cout << order->getType() << " order for " << order->getUser()->getName() << " | Total: $" << order->getTotal() << " | At: " << order->getScheduled() << endl;
        }
    }
    
};

OrderManager* OrderManager::instance = nullptr;

#endif
