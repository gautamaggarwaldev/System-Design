#ifndef ORDER_H
#define ORDER_H

#include<iostream>
#include<vector>
#include<string>
#include "User.h"
#include "Restaurant.h"
#include "MenuItem.h"
#include "../utils/TimeUtils.h"
#include "../strategies/PaymentStrategy.h"
using namespace std;

class Order {
protected:
    static int nextOrderId;
    int orderId;
    User* user;
    Restaurant* restaurant;
    vector<MenuItem> items;
    PaymentStrategy* paymentStarategy;
    double total;
    string scheduled;

public: 
    Order() {
        user = nullptr;
        restaurant = nullptr;
        paymentStarategy = nullptr;
        total = 0.0;
        scheduled = "";
        orderId = ++nextOrderId;
    }

    virtual ~Order() {
        delete paymentStarategy;
    }

    bool processPayment() {
        if(paymentStarategy) {
            paymentStarategy->pay(total);
            return true;
        }
        else {
            cout << "Please choose a payment mode first" << endl;
            return false;
        }
    }

    virtual string getType() const = 0;

    // Getter and Setters
    int getOrderId() const {
        return orderId;
    }

    void setUser(User* u) {
        user = u;
    }

    User* getUser() const {
        return user;
    }

    void setRestaurant(Restaurant* r) {
        restaurant = r;
    }

    Restaurant* getRestaurant() {
        return restaurant;
    }

    void setItems(const vector<MenuItem>& its) {
        items = its;
        total = 0;
        for(auto& i : items) {
            total += i.getPrice();
        }
    }

    const vector<MenuItem>& getItems() const {
        return items;
    }

    void setPaymentStrategy(PaymentStrategy* p) {
        paymentStarategy = p;
    }

    void setScheduled(const string& s) {
        scheduled = s;
    }

    string getScheduled() const {
        return scheduled;
    }

    double getTotal() const {
        return total;
    }

    void setTotal(int total) {
        this->total = total;
    }
};

int Order::nextOrderId = 0;

#endif
