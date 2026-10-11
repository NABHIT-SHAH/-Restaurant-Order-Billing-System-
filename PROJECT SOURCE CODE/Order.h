#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <iostream>

using namespace std;

// Order class demonstrating dynamic memory management
class Order {
private:
    int orderId;
    int customerId;
    int* itemIds;       // Dynamic array - allocated with new[]
    int* quantities;    // Dynamic array - allocated with new[]
    int itemCount;
    int capacity;
    string status;      // Pending, Completed, Cancelled
    string orderDate;

    void resize();      // Double capacity when full

public:
    Order();
    Order(int orderId, int customerId);
    Order(const Order& other);              // Copy constructor (Rule of Three)
    Order& operator=(const Order& other);   // Copy assignment (Rule of Three)
    ~Order();                               // Destructor frees dynamic memory

    // Getters
    int getOrderId() const;
    int getCustomerId() const;
    int getItemCount() const;
    int getItemId(int index) const;
    int getQuantity(int index) const;
    string getStatus() const;
    string getOrderDate() const;

    // Setters
    void setOrderId(int id);
    void setCustomerId(int id);
    void setStatus(const string& s);
    void setOrderDate(const string& d);

    void addItem(int itemId, int quantity);
    void removeItem(int itemId);
    void display() const;
    string toFileString() const;
    void fromFileString(const string& line);
};

#endif
