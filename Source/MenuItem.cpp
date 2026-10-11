#include "MenuItem.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

// Default constructor initializes default values
MenuItem::MenuItem()
    : itemId(0), name(""), price(0.0), category(""), available(true) {}

// Parameterized constructor
MenuItem::MenuItem(int itemId, const string& name, double price, const string& category)
    : itemId(itemId), name(name), price(price), category(category), available(true) {}

// Virtual destructor
MenuItem::~MenuItem() {
    // Empty body - virtual destructor ensures proper cleanup of derived objects
}

// Getters
int MenuItem::getItemId() const {
    return itemId;
}

string MenuItem::getName() const {
    return name;
}

double MenuItem::getPrice() const {
    return price;
}

string MenuItem::getCategory() const {
    return category;
}

bool MenuItem::isAvailable() const {
    return available;
}

// Setters
void MenuItem::setItemId(int id) {
    itemId = id;
}

void MenuItem::setName(const string& n) {
    name = n;
}

void MenuItem::setPrice(double p) {
    price = p;
}

void MenuItem::setCategory(const string& c) {
    category = c;
}

void MenuItem::setAvailable(bool a) {
    available = a;
}

// Display formatted item information
void MenuItem::display() const {
    cout << left << setw(6) << itemId 
         << setw(25) << name 
         << setw(12) << fixed << setprecision(2) << price 
         << setw(15) << category 
         << (available ? "Yes" : "No") << endl;
}

// Returns the type of item
string MenuItem::getType() const {
    return "GENERIC";
}

// Serializes item data to a pipe-delimited string
string MenuItem::toFileString() const {
    return "GENERIC|" + to_string(itemId) + "|" + name + "|" + to_string(price) + "|" + category + "|" + to_string(available ? 1 : 0);
}

// Deserializes item data from a pipe-delimited string
void MenuItem::fromFileString(const string& line) {
    stringstream ss(line);
    string token;

    // Skip type token
    if (getline(ss, token, '|')) {
        // token is type
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
}
