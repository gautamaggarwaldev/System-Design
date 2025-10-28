#ifndef RESTAURANT_H
#define RESTAURANT_H

#include<iostream>
#include<vector>
#include<string>
#include "MenuItem.h"
using namespace std;

class Restaurant {
private:
    static int nextRestaurantId;
    int restaurantid;
    string name;
    string location;
    vector<MenuItem> menu;
    
public:
    Restaurant(const string& name, const string& location) {
        this->name = name;
        this->location = location;
        this->restaurantid = ++nextRestaurantId;
    }

    ~Restaurant() {
        cout << "Destroying restaurant: " << name << " and clearing its menu" << endl;
        menu.clear(); 
    }

    //Getters and Setters

    string getName() const {
        return name;
    }

    void setName(const string& n) {
        name = n;
    }

    string getLocation() const {
        return location;
    }

    void setLocation(const string& l) {
        location = l;
    }

    void addMenuItem(const MenuItem& item) {
        menu.push_back(item);
    }

    const vector<MenuItem>& getMenu() const {
        return menu;
    }
};

int Restaurant::nextRestaurantId = 0;

#endif