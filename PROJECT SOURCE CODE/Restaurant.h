#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "MenuItem.h"
#include "FoodItem.h"
#include "BeverageItem.h"
#include "Customer.h"
#include "Order.h"
#include "Bill.h"
#include "FileManager.h"

// Main system class - manages all restaurant operations
class Restaurant {
private:
    MenuItem** menuItems;   // Dynamic array of pointers for polymorphism
    Customer* customers;    // Dynamic array
    Order* orders;          // Dynamic array
    Bill* bills;            // Dynamic array

    int menuCount, customerCount, orderCount, billCount;
    int menuCapacity, customerCapacity, orderCapacity, billCapacity;

    FileManager fileManager;
    string dataPath;

    // Private helpers
    void resizeMenu();
    void resizeCustomers();
    void resizeOrders();
    void resizeBills();

    int findMenuItemIndex(int id) const;
    int findCustomerIndex(int id) const;
    int findOrderIndex(int id) const;
    int findBillIndex(int id) const;

    int getNextMenuItemId() const;
    int getNextCustomerId() const;
    int getNextOrderId() const;
    int getNextBillId() const;

    // Sub-menu helpers
    void addRecordMenu();
    void displayRecordMenu() const;
    void searchRecordMenu() const;
    void updateRecordMenu();
    void deleteRecordMenu();

public:
    Restaurant();
    ~Restaurant();

    void run();  // Main loop

    // Menu Item operations
    void addMenuItem();
    void displayMenuItems() const;
    void searchMenuItem() const;
    void updateMenuItem();
    void deleteMenuItem();

    // Customer operations
    void addCustomer();
    void displayCustomers() const;
    void searchCustomer() const;
    void updateCustomer();
    void deleteCustomer();

    // Order operations
    void displayOrders() const;
    void searchOrder() const;
    void updateOrderStatus();
    void deleteOrder();

    // Bill operations
    void displayBills() const;
    void searchBill() const;

    // Main Transaction
    void placeOrder();

    // Report
    void generateReport() const;

    // File operations
    void saveData();
    void loadData();
};

#endif
