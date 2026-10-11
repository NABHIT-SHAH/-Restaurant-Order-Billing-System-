#ifndef BEVERAGEITEM_H
#define BEVERAGEITEM_H

#include "MenuItem.h"

// Derived class demonstrating inheritance and polymorphism
class BeverageItem : public MenuItem {
private:
    string size;  // Small, Medium, Large
    bool isHot;   // Hot or Cold

public:
    BeverageItem();
    BeverageItem(int itemId, const string& name, double price, const string& category,
                 const string& size, bool isHot);
    ~BeverageItem() override;

    string getSize() const;
    bool getIsHot() const;
    void setSize(const string& s);
    void setIsHot(bool hot);

    void display() const override;
    string getType() const override;
    string toFileString() const override;
    void fromFileString(const string& line) override;
};

#endif // BEVERAGEITEM_H
