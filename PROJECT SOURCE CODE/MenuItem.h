#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
#include <iostream>

using namespace std;

// Base class for all menu items - demonstrates runtime polymorphism
class MenuItem {
protected:
    int itemId;
    string name;
    double price;
    string category;
    bool available;

public:
    // Constructors and destructor
    MenuItem();
    MenuItem(int itemId, const string& name, double price, const string& category);
    virtual ~MenuItem();

    // Getters
    int getItemId() const;
    string getName() const;
    double getPrice() const;
    string getCategory() const;
    bool isAvailable() const;

    // Setters
    void setItemId(int id);
    void setName(const string& n);
    void setPrice(double p);
    void setCategory(const string& c);
    void setAvailable(bool a);

    // Virtual functions for runtime polymorphism
    virtual void display() const;
    virtual string getType() const;
    virtual string toFileString() const;
    virtual void fromFileString(const string& line);
};

#endif // MENUITEM_H
