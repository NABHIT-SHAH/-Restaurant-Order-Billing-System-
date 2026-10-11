#include "FoodItem.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

// Default constructor
FoodItem::FoodItem()
    : MenuItem(), cuisineType(""), isVeg(true) {}

// Parameterized constructor
FoodItem::FoodItem(int itemId, const string& name, double price, const string& category,
                   const string& cuisineType, bool isVeg)
    : MenuItem(itemId, name, price, category), cuisineType(cuisineType), isVeg(isVeg) {}

// Destructor
FoodItem::~FoodItem() {
    // Empty body
}

// Getters
string FoodItem::getCuisineType() const {
    return cuisineType;
}

bool FoodItem::getIsVeg() const {
    return isVeg;
}

// Setters
void FoodItem::setCuisineType(const string& type) {
    cuisineType = type;
}

void FoodItem::setIsVeg(bool veg) {
    isVeg = veg;
}

// Display formatted food item information
void FoodItem::display() const {
    cout << left << setw(6) << itemId 
         << setw(25) << name 
         << "Rs." << setw(10) << fixed << setprecision(2) << price 
         << setw(15) << category 
         << setw(12) << cuisineType 
         << setw(10) << (isVeg ? "Veg" : "Non-Veg") 
         << (available ? "Yes" : "No") << endl;
}

// Returns item type
string FoodItem::getType() const {
    return "FOOD";
}

// Serializes food item data to a pipe-delimited string
string FoodItem::toFileString() const {
    return "FOOD|" + to_string(itemId) + "|" + name + "|" + to_string(price) + "|" 
           + category + "|" + to_string(available ? 1 : 0) + "|" 
           + cuisineType + "|" + to_string(isVeg ? 1 : 0);
}

// Deserializes food item data from a pipe-delimited string
void FoodItem::fromFileString(const string& line) {
    stringstream ss(line);
    string token;

    // Skip type token
    if (getline(ss, token, '|')) {
        // token is "FOOD"
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
        cuisineType = token;
    }
    if (getline(ss, token, '|')) {
        isVeg = (token == "1" || token == "true");
    }
}
