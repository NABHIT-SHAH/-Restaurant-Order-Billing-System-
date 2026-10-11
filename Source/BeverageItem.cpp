#include "BeverageItem.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

// Default constructor
BeverageItem::BeverageItem()
    : MenuItem(), size("Medium"), isHot(false) {}

// Parameterized constructor
BeverageItem::BeverageItem(int itemId, const string& name, double price, const string& category,
                           const string& size, bool isHot)
    : MenuItem(itemId, name, price, category), size(size), isHot(isHot) {}

// Destructor
BeverageItem::~BeverageItem() {
    // Empty body
}

// Getters
string BeverageItem::getSize() const {
    return size;
}

bool BeverageItem::getIsHot() const {
    return isHot;
}

// Setters
void BeverageItem::setSize(const string& s) {
    size = s;
}

void BeverageItem::setIsHot(bool hot) {
    isHot = hot;
}

// Display formatted beverage item information
void BeverageItem::display() const {
    cout << left << setw(6) << itemId 
         << setw(25) << name 
         << "Rs." << setw(10) << fixed << setprecision(2) << price 
         << setw(15) << category 
         << setw(10) << size 
         << setw(8) << (isHot ? "Hot" : "Cold") 
         << (available ? "Yes" : "No") << endl;
}

// Returns item type
string BeverageItem::getType() const {
    return "BEVERAGE";
}

// Serializes beverage item data to a pipe-delimited string
string BeverageItem::toFileString() const {
    return "BEVERAGE|" + to_string(itemId) + "|" + name + "|" + to_string(price) + "|" 
           + category + "|" + to_string(available ? 1 : 0) + "|" 
           + size + "|" + to_string(isHot ? 1 : 0);
}

// Deserializes beverage item data from a pipe-delimited string
void BeverageItem::fromFileString(const string& line) {
    stringstream ss(line);
    string token;

    // Skip type token
    if (getline(ss, token, '|')) {
        // token is "BEVERAGE"
    }
    if (getline(ss, token, '|')) {
        itemId = stoi(token);
    }
    if (getline(ss, token, '|')) {
        name = token;
    }
    if (getline(ss, token, '|')) {
        price = stod(token);
    }
    if (getline(ss, token, '|')) {
        category = token;
    }
    if (getline(ss, token, '|')) {
        available = (token == "1" || token == "true");
    }
    if (getline(ss, token, '|')) {
        size = token;
    }
    if (getline(ss, token, '|')) {
        isHot = (token == "1" || token == "true");
    }
}
