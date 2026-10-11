#include "FileManager.h"
#include "MenuItem.h"
#include "FoodItem.h"
#include "BeverageItem.h"
#include "Customer.h"
#include "Order.h"
#include "Bill.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

using namespace std;

// Default constructor
FileManager::FileManager() {
}

// Destructor
FileManager::~FileManager() {
}

// Save menu items to file
void FileManager::saveMenuItems(MenuItem** items, int count, const string& filename) const {
    ofstream outFile(filename.c_str());
    if (!outFile.is_open()) {
        throw runtime_error("Failed to open file for writing: " + filename);
    }

    for (int i = 0; i < count; i++) {
        if (items[i] != nullptr) {
            outFile << items[i]->toFileString() << "\n";
        }
    }

    outFile.close();
    cout << "Successfully saved " << count << " menu items to " << filename << endl;
}

// Save customers to file
void FileManager::saveCustomers(Customer* customers, int count, const string& filename) const {
    ofstream outFile(filename.c_str());
    if (!outFile.is_open()) {
        throw runtime_error("Failed to open file for writing: " + filename);
    }

    for (int i = 0; i < count; i++) {
        outFile << customers[i].toFileString() << "\n";
    }

    outFile.close();
    cout << "Successfully saved " << count << " customers to " << filename << endl;
}

// Save orders to file
void FileManager::saveOrders(Order* orders, int count, const string& filename) const {
    ofstream outFile(filename.c_str());
    if (!outFile.is_open()) {
        throw runtime_error("Failed to open file for writing: " + filename);
    }

    for (int i = 0; i < count; i++) {
        outFile << orders[i].toFileString() << "\n";
    }

    outFile.close();
    cout << "Successfully saved " << count << " orders to " << filename << endl;
}

// Save bills to file
void FileManager::saveBills(Bill* bills, int count, const string& filename) const {
    ofstream outFile(filename.c_str());
    if (!outFile.is_open()) {
        throw runtime_error("Failed to open file for writing: " + filename);
    }

    for (int i = 0; i < count; i++) {
        outFile << bills[i].toFileString() << "\n";
    }

    outFile.close();
    cout << "Successfully saved " << count << " bills to " << filename << endl;
}

// Load menu items from file polymorphically
int FileManager::loadMenuItems(MenuItem**& items, int& capacity, const string& filename) const {
    try {
        ifstream inFile(filename.c_str());
        if (!inFile.is_open()) {
            return 0;
        }

        int count = 0;
        string line;
        while (getline(inFile, line)) {
            if (line.empty()) continue;

            // Resize array if capacity reached
            if (count >= capacity) {
                int newCapacity = (capacity <= 0) ? 5 : capacity * 2;
                MenuItem** newItems = new MenuItem*[newCapacity];
                for (int i = 0; i < count; i++) {
                    newItems[i] = items[i];
                }
                delete[] items;
                items = newItems;
                capacity = newCapacity;
            }

            // Extract item type prefix
            stringstream ss(line);
            string type;
            getline(ss, type, '|');

            if (type == "FOOD") {
                FoodItem* fi = new FoodItem();
                fi->fromFileString(line);
                items[count] = fi;
            } else if (type == "BEVERAGE") {
                BeverageItem* bi = new BeverageItem();
                bi->fromFileString(line);
                items[count] = bi;
            } else {
                MenuItem* mi = new MenuItem();
                mi->fromFileString(line);
                items[count] = mi;
            }
            count++;
        }

        inFile.close();
        cout << "Successfully loaded " << count << " menu items from " << filename << endl;
        return count;
    } catch (const exception& e) {
        cerr << "Error loading menu items: " << e.what() << endl;
        return 0;
    }
}

// Load customers from file
int FileManager::loadCustomers(Customer*& customers, int& capacity, const string& filename) const {
    try {
        ifstream inFile(filename.c_str());
        if (!inFile.is_open()) {
            return 0;
        }

        int count = 0;
        string line;
        while (getline(inFile, line)) {
            if (line.empty()) continue;

            // Resize array if capacity reached
            if (count >= capacity) {
                int newCapacity = (capacity <= 0) ? 5 : capacity * 2;
                Customer* newCustomers = new Customer[newCapacity];
                for (int i = 0; i < count; i++) {
                    newCustomers[i] = customers[i];
                }
                delete[] customers;
                customers = newCustomers;
                capacity = newCapacity;
            }

            customers[count].fromFileString(line);
            count++;
        }

        inFile.close();
        cout << "Successfully loaded " << count << " customers from " << filename << endl;
        return count;
    } catch (const exception& e) {
        cerr << "Error loading customers: " << e.what() << endl;
        return 0;
    }
}

// Load orders from file
int FileManager::loadOrders(Order*& orders, int& capacity, const string& filename) const {
    try {
        ifstream inFile(filename.c_str());
        if (!inFile.is_open()) {
            return 0;
        }

        int count = 0;
        string line;
        while (getline(inFile, line)) {
            if (line.empty()) continue;

            // Resize array if capacity reached
            if (count >= capacity) {
                int newCapacity = (capacity <= 0) ? 5 : capacity * 2;
                Order* newOrders = new Order[newCapacity];
                for (int i = 0; i < count; i++) {
                    newOrders[i] = orders[i];
                }
                delete[] orders;
                orders = newOrders;
                capacity = newCapacity;
            }

            orders[count].fromFileString(line);
            count++;
        }

        inFile.close();
        cout << "Successfully loaded " << count << " orders from " << filename << endl;
        return count;
    } catch (const exception& e) {
        cerr << "Error loading orders: " << e.what() << endl;
        return 0;
    }
}

// Load bills from file
int FileManager::loadBills(Bill*& bills, int& capacity, const string& filename) const {
    try {
        ifstream inFile(filename.c_str());
        if (!inFile.is_open()) {
            return 0;
        }

        int count = 0;
        string line;
        while (getline(inFile, line)) {
            if (line.empty()) continue;

            // Resize array if capacity reached
            if (count >= capacity) {
                int newCapacity = (capacity <= 0) ? 5 : capacity * 2;
                Bill* newBills = new Bill[newCapacity];
                for (int i = 0; i < count; i++) {
                    newBills[i] = bills[i];
                }
                delete[] bills;
                bills = newBills;
                capacity = newCapacity;
            }

            bills[count].fromFileString(line);
            count++;
        }

        inFile.close();
        cout << "Successfully loaded " << count << " bills from " << filename << endl;
        return count;
    } catch (const exception& e) {
        cerr << "Error loading bills: " << e.what() << endl;
        return 0;
    }
}
