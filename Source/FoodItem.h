#ifndef FOODITEM_H
#define FOODITEM_H

#include "MenuItem.h"

// Derived class demonstrating inheritance and polymorphism
class FoodItem : public MenuItem {
private:
    string cuisineType;  // e.g., Indian, Chinese, Italian
    bool isVeg;

public:
    FoodItem();
    FoodItem(int itemId, const string& name, double price, const string& category,
             const string& cuisineType, bool isVeg);
    ~FoodItem() override;

    string getCuisineType() const;
    bool getIsVeg() const;
    void setCuisineType(const string& type);
    void setIsVeg(bool veg);

    void display() const override;
    string getType() const override;
    string toFileString() const override;
    void fromFileString(const string& line) override;
};

#endif // FOODITEM_H
