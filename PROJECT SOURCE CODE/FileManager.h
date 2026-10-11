#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

// Forward declarations to avoid circular includes
class MenuItem;
class Customer;
class Order;
class Bill;

class FileManager {
public:
    FileManager();
    ~FileManager();

    // Save functions
    void saveMenuItems(MenuItem** items, int count, const string& filename) const;
    void saveCustomers(Customer* customers, int count, const string& filename) const;
    void saveOrders(Order* orders, int count, const string& filename) const;
    void saveBills(Bill* bills, int count, const string& filename) const;

    // Load functions - return the count of loaded items
    int loadMenuItems(MenuItem**& items, int& capacity, const string& filename) const;
    int loadCustomers(Customer*& customers, int& capacity, const string& filename) const;
    int loadOrders(Order*& orders, int& capacity, const string& filename) const;
    int loadBills(Bill*& bills, int& capacity, const string& filename) const;
};

#endif
