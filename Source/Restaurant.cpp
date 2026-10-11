#include "Restaurant.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <algorithm>
#include <limits>
#include <vector>

using namespace std;

// Helper: Convert string to lowercase for case-insensitive search
static string toLowerStr(const string& str) {
    string lower = str;
    transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) {
        return tolower(c);
    });
    return lower;
}

// Helper: Validate 10-digit phone number
static bool isValidPhoneNumber(const string& phone) {
    if (phone.length() != 10) return false;
    for (char c : phone) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// Constructor: Initialize counts, capacities, and allocate dynamic arrays
Restaurant::Restaurant() : menuCount(0), customerCount(0), orderCount(0), billCount(0),
    menuCapacity(10), customerCapacity(10), orderCapacity(10), billCapacity(10),
    dataPath("Data/") {
    menuItems = new MenuItem*[menuCapacity];
    customers = new Customer[customerCapacity];
    orders = new Order[orderCapacity];
    bills = new Bill[billCapacity];
    // Initialize pointers to nullptr
    for (int i = 0; i < menuCapacity; i++) {
        menuItems[i] = nullptr;
    }
}

// Destructor: Clean up dynamically allocated memory
Restaurant::~Restaurant() {
    for (int i = 0; i < menuCount; i++) {
        delete menuItems[i];  // Delete each MenuItem object polymorphically
    }
    delete[] menuItems;       // Delete pointer array
    delete[] customers;
    delete[] orders;
    delete[] bills;
}

// Resize dynamic array of MenuItem pointers
void Restaurant::resizeMenu() {
    int newCapacity = menuCapacity * 2;
    MenuItem** newItems = new MenuItem*[newCapacity];
    for (int i = 0; i < menuCount; i++) {
        newItems[i] = menuItems[i];
    }
    for (int i = menuCount; i < newCapacity; i++) {
        newItems[i] = nullptr;
    }
    delete[] menuItems;
    menuItems = newItems;
    menuCapacity = newCapacity;
}

// Resize dynamic array of Customers
void Restaurant::resizeCustomers() {
    int newCapacity = customerCapacity * 2;
    Customer* newCustomers = new Customer[newCapacity];
    for (int i = 0; i < customerCount; i++) {
        newCustomers[i] = customers[i];
    }
    delete[] customers;
    customers = newCustomers;
    customerCapacity = newCapacity;
}

// Resize dynamic array of Orders
void Restaurant::resizeOrders() {
    int newCapacity = orderCapacity * 2;
    Order* newOrders = new Order[newCapacity];
    for (int i = 0; i < orderCount; i++) {
        newOrders[i] = orders[i];
    }
    delete[] orders;
    orders = newOrders;
    orderCapacity = newCapacity;
}

// Resize dynamic array of Bills
void Restaurant::resizeBills() {
    int newCapacity = billCapacity * 2;
    Bill* newBills = new Bill[newCapacity];
    for (int i = 0; i < billCount; i++) {
        newBills[i] = bills[i];
    }
    delete[] bills;
    bills = newBills;
    billCapacity = newCapacity;
}

// Find index of MenuItem by ID, returns -1 if not found
int Restaurant::findMenuItemIndex(int id) const {
    for (int i = 0; i < menuCount; i++) {
        if (menuItems[i] != nullptr && menuItems[i]->getItemId() == id) {
            return i;
        }
    }
    return -1;
}

// Find index of Customer by ID, returns -1 if not found
int Restaurant::findCustomerIndex(int id) const {
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].getCustomerId() == id) {
            return i;
        }
    }
    return -1;
}

// Find index of Order by ID, returns -1 if not found
int Restaurant::findOrderIndex(int id) const {
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].getOrderId() == id) {
            return i;
        }
    }
    return -1;
}

// Find index of Bill by ID, returns -1 if not found
int Restaurant::findBillIndex(int id) const {
    for (int i = 0; i < billCount; i++) {
        if (bills[i].getBillId() == id) {
            return i;
        }
    }
    return -1;
}

// Get next available ID for MenuItem
int Restaurant::getNextMenuItemId() const {
    int maxId = 0;
    for (int i = 0; i < menuCount; i++) {
        if (menuItems[i] != nullptr && menuItems[i]->getItemId() > maxId) {
            maxId = menuItems[i]->getItemId();
        }
    }
    return maxId + 1;
}

// Get next available ID for Customer
int Restaurant::getNextCustomerId() const {
    int maxId = 0;
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].getCustomerId() > maxId) {
            maxId = customers[i].getCustomerId();
        }
    }
    return maxId + 1;
}

// Get next available ID for Order
int Restaurant::getNextOrderId() const {
    int maxId = 0;
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].getOrderId() > maxId) {
            maxId = orders[i].getOrderId();
        }
    }
    return maxId + 1;
}

// Get next available ID for Bill
int Restaurant::getNextBillId() const {
    int maxId = 0;
    for (int i = 0; i < billCount; i++) {
        if (bills[i].getBillId() > maxId) {
            maxId = bills[i].getBillId();
        }
    }
    return maxId + 1;
}

// Sub-menu for adding records
void Restaurant::addRecordMenu() {
    cout << "\n--- ADD RECORD ---" << endl;
    cout << "1. Menu Item" << endl;
    cout << "2. Customer" << endl;
    cout << "3. Back" << endl;
    cout << "Enter choice: ";
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input!\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (choice) {
        case 1: addMenuItem(); break;
        case 2: addCustomer(); break;
        case 3: break;
        default: cout << "Invalid choice!\n"; break;
    }
}

// Sub-menu for displaying records
void Restaurant::displayRecordMenu() const {
    cout << "\n--- DISPLAY RECORDS ---" << endl;
    cout << "1. Menu Items" << endl;
    cout << "2. Customers" << endl;
    cout << "3. Orders" << endl;
    cout << "4. Bills" << endl;
    cout << "5. Back" << endl;
    cout << "Enter choice: ";
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input!\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (choice) {
        case 1: displayMenuItems(); break;
        case 2: displayCustomers(); break;
        case 3: displayOrders(); break;
        case 4: displayBills(); break;
        case 5: break;
        default: cout << "Invalid choice!\n"; break;
    }
}

// Sub-menu for searching records
void Restaurant::searchRecordMenu() const {
    cout << "\n--- SEARCH RECORD ---" << endl;
    cout << "1. Menu Item" << endl;
    cout << "2. Customer" << endl;
    cout << "3. Order" << endl;
    cout << "4. Bill" << endl;
    cout << "5. Back" << endl;
    cout << "Enter choice: ";
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input!\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (choice) {
        case 1: searchMenuItem(); break;
        case 2: searchCustomer(); break;
        case 3: searchOrder(); break;
        case 4: searchBill(); break;
        case 5: break;
        default: cout << "Invalid choice!\n"; break;
    }
}

// Sub-menu for updating records
void Restaurant::updateRecordMenu() {
    cout << "\n--- UPDATE RECORD ---" << endl;
    cout << "1. Menu Item" << endl;
    cout << "2. Customer" << endl;
    cout << "3. Order Status" << endl;
    cout << "4. Back" << endl;
    cout << "Enter choice: ";
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input!\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (choice) {
        case 1: updateMenuItem(); break;
        case 2: updateCustomer(); break;
        case 3: updateOrderStatus(); break;
        case 4: break;
        default: cout << "Invalid choice!\n"; break;
    }
}

// Sub-menu for deleting records
void Restaurant::deleteRecordMenu() {
    cout << "\n--- DELETE RECORD ---" << endl;
    cout << "1. Menu Item" << endl;
    cout << "2. Customer" << endl;
    cout << "3. Order" << endl;
    cout << "4. Back" << endl;
    cout << "Enter choice: ";
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input!\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (choice) {
        case 1: deleteMenuItem(); break;
        case 2: deleteCustomer(); break;
        case 3: deleteOrder(); break;
        case 4: break;
        default: cout << "Invalid choice!\n"; break;
    }
}

// Main interactive loop
void Restaurant::run() {
    loadData();  // Load existing data on startup
    int choice = 0;
    do {
        cout << "\n========================================" << endl;
        cout << "  RESTAURANT ORDER & BILLING SYSTEM" << endl;
        cout << "  Enrollment: IU2541230417 | CPP07" << endl;
        cout << "========================================" << endl;
        cout << "1. Add Record" << endl;
        cout << "2. Display Records" << endl;
        cout << "3. Search Record" << endl;
        cout << "4. Update Record" << endl;
        cout << "5. Delete Record" << endl;
        cout << "6. Place Order (Main Transaction)" << endl;
        cout << "7. Generate Report" << endl;
        cout << "8. Save/Load Data" << endl;
        cout << "9. Exit" << endl;
        cout << "========================================" << endl;
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between 1 and 9.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        try {
            switch (choice) {
                case 1: addRecordMenu(); break;
                case 2: displayRecordMenu(); break;
                case 3: searchRecordMenu(); break;
                case 4: updateRecordMenu(); break;
                case 5: deleteRecordMenu(); break;
                case 6: placeOrder(); break;
                case 7: generateReport(); break;
                case 8: {
                    cout << "\n1. Save Data\n2. Load Data\nChoice: ";
                    int sc;
                    if (cin >> sc) {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (sc == 1) saveData();
                        else if (sc == 2) loadData();
                        else cout << "Invalid choice!\n";
                    } else {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input!\n";
                    }
                    break;
                }
                case 9:
                    saveData();  // Auto-save on exit
                    cout << "\nData saved. Thank you for using the system!\n";
                    break;
                default:
                    cout << "Invalid choice! Please select between 1 and 9.\n";
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    } while (choice != 9);
}

// Add a new MenuItem (FoodItem or BeverageItem)
void Restaurant::addMenuItem() {
    cout << "\n--- ADD MENU ITEM ---" << endl;
    cout << "Select Type:\n1. Food Item\n2. Beverage Item\nEnter choice: ";
    int typeChoice;
    if (!(cin >> typeChoice) || (typeChoice != 1 && typeChoice != 2)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid type choice! Cancelled.\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string name;
    cout << "Enter Name: ";
    getline(cin, name);
    if (name.empty()) {
        cout << "Error: Name cannot be empty!\n";
        return;
    }

    double price;
    cout << "Enter Price: ";
    if (!(cin >> price) || price <= 0.0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: Invalid price! Must be greater than 0.\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string category;
    cout << "Enter Category (e.g. Starter, Main Course, Dessert, Drinks): ";
    getline(cin, category);

    int id = getNextMenuItemId();
    MenuItem* newItem = nullptr;

    if (typeChoice == 1) {
        string cuisine;
        cout << "Enter Cuisine Type (e.g. Indian, Chinese, Italian): ";
        getline(cin, cuisine);

        cout << "Is it Vegetarian? (1 for Yes, 0 for No): ";
        int vegInt;
        if (!(cin >> vegInt) || (vegInt != 0 && vegInt != 1)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Defaulting to Vegetarian.\n";
            vegInt = 1;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        bool isVeg = (vegInt == 1);

        newItem = new FoodItem(id, name, price, category, cuisine, isVeg);
    } else {
        string size;
        cout << "Enter Size (Small / Medium / Large): ";
        getline(cin, size);

        cout << "Is it Hot? (1 for Hot, 0 for Cold): ";
        int hotInt;
        if (!(cin >> hotInt) || (hotInt != 0 && hotInt != 1)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Defaulting to Cold.\n";
            hotInt = 0;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        bool isHot = (hotInt == 1);

        newItem = new BeverageItem(id, name, price, category, size, isHot);
    }

    if (menuCount >= menuCapacity) {
        resizeMenu();
    }
    menuItems[menuCount++] = newItem;
    cout << "Menu Item added successfully with ID: " << id << endl;
}

// Display all MenuItems polymorphically
void Restaurant::displayMenuItems() const {
    if (menuCount == 0) {
        cout << "\nNo menu items found.\n";
        return;
    }
    cout << "\n============================== MENU ITEMS ==============================" << endl;
    for (int i = 0; i < menuCount; i++) {
        if (menuItems[i] != nullptr) {
            menuItems[i]->display();
            cout << "------------------------------------------------------------------------" << endl;
        }
    }
}

// Search MenuItem by ID or Name
void Restaurant::searchMenuItem() const {
    if (menuCount == 0) {
        cout << "\nNo menu items available to search.\n";
        return;
    }
    cout << "\n--- SEARCH MENU ITEM ---" << endl;
    cout << "1. Search by ID\n2. Search by Name\nEnter choice: ";
    int opt;
    if (!(cin >> opt)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid option!\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (opt == 1) {
        cout << "Enter Menu Item ID: ";
        int id;
        if (!(cin >> id)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid ID!\n";
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int idx = findMenuItemIndex(id);
        if (idx == -1) {
            cout << "Menu item with ID " << id << " not found!\n";
        } else {
            cout << "\nItem Found:\n";
            menuItems[idx]->display();
        }
    } else if (opt == 2) {
        cout << "Enter search keyword for Name: ";
        string query;
        getline(cin, query);
        string lowerQuery = toLowerStr(query);

        bool found = false;
        cout << "\n--- SEARCH RESULTS ---" << endl;
        for (int i = 0; i < menuCount; i++) {
            if (menuItems[i] != nullptr) {
                string lowerName = toLowerStr(menuItems[i]->getName());
                if (lowerName.find(lowerQuery) != string::npos) {
                    menuItems[i]->display();
                    cout << "------------------------------------------------------------------------" << endl;
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "No menu items matched \"" << query << "\".\n";
        }
    } else {
        cout << "Invalid choice!\n";
    }
}

// Update fields of an existing MenuItem
void Restaurant::updateMenuItem() {
    if (menuCount == 0) {
        cout << "\nNo menu items to update.\n";
        return;
    }
    cout << "Enter Menu Item ID to update: ";
    int id;
    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID!\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int idx = findMenuItemIndex(id);
    if (idx == -1) {
        cout << "Menu item with ID " << id << " not found!\n";
        return;
    }

    cout << "\nCurrent Details:\n";
    menuItems[idx]->display();

    cout << "\nWhat would you like to update?\n";
    cout << "1. Name\n2. Price\n3. Category\n4. Availability\nEnter choice: ";
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice!\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (choice) {
        case 1: {
            cout << "Enter new Name: ";
            string newName;
            getline(cin, newName);
            if (!newName.empty()) {
                menuItems[idx]->setName(newName);
                cout << "Name updated successfully!\n";
            } else {
                cout << "Name cannot be empty!\n";
            }
            break;
        }
        case 2: {
            cout << "Enter new Price: ";
            double newPrice;
            if (cin >> newPrice && newPrice > 0.0) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                menuItems[idx]->setPrice(newPrice);
                cout << "Price updated successfully!\n";
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid price!\n";
            }
            break;
        }
        case 3: {
            cout << "Enter new Category: ";
            string newCat;
            getline(cin, newCat);
            menuItems[idx]->setCategory(newCat);
            cout << "Category updated successfully!\n";
            break;
        }
        case 4: {
            cout << "Enter Availability (1 for Available, 0 for Unavailable): ";
            int avail;
            if (cin >> avail && (avail == 0 || avail == 1)) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                menuItems[idx]->setAvailable(avail == 1);
                cout << "Availability updated successfully!\n";
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input!\n";
            }
            break;
        }
        default:
            cout << "Invalid option!\n";
            break;
    }
}

// Delete MenuItem and shift remaining elements
void Restaurant::deleteMenuItem() {
    if (menuCount == 0) {
        cout << "\nNo menu items to delete.\n";
        return;
    }
    cout << "Enter Menu Item ID to delete: ";
    int id;
    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID!\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int idx = findMenuItemIndex(id);
    if (idx == -1) {
        cout << "Menu item with ID " << id << " not found!\n";
        return;
    }

    cout << "Are you sure you want to delete '" << menuItems[idx]->getName() << "'? (y/n): ";
    char confirm;
    cin >> confirm;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (confirm == 'y' || confirm == 'Y') {
        delete menuItems[idx];
        for (int i = idx; i < menuCount - 1; i++) {
            menuItems[i] = menuItems[i + 1];
        }
        menuItems[menuCount - 1] = nullptr;
        menuCount--;
        cout << "Menu Item deleted successfully!\n";
    } else {
        cout << "Deletion cancelled.\n";
    }
}

// Add a new Customer
void Restaurant::addCustomer() {
    cout << "\n--- ADD CUSTOMER ---" << endl;
    cout << "Enter Customer Name: ";
    string name;
    getline(cin, name);
    if (name.empty()) {
        cout << "Customer name cannot be empty!\n";
        return;
    }

    cout << "Enter 10-digit Phone Number: ";
    string phone;
    getline(cin, phone);
    if (!isValidPhoneNumber(phone)) {
        cout << "Error: Phone number must be exactly 10 digits!\n";
        return;
    }

    cout << "Enter Address: ";
    string address;
    getline(cin, address);

    int id = getNextCustomerId();
    if (customerCount >= customerCapacity) {
        resizeCustomers();
    }

    customers[customerCount++] = Customer(id, name, phone, address);
    cout << "Customer registered successfully with ID: " << id << endl;
}

// Display all Customers
void Restaurant::displayCustomers() const {
    if (customerCount == 0) {
        cout << "\nNo customers found.\n";
        return;
    }
    cout << "\n================================ CUSTOMERS ================================" << endl;
    for (int i = 0; i < customerCount; i++) {
        customers[i].display();
        cout << "------------------------------------------------------------------------" << endl;
    }
}

// Search Customer by ID or Name
void Restaurant::searchCustomer() const {
    if (customerCount == 0) {
        cout << "\nNo customers to search.\n";
        return;
    }
    cout << "\n--- SEARCH CUSTOMER ---" << endl;
    cout << "1. Search by ID\n2. Search by Name\nEnter choice: ";
    int opt;
    if (!(cin >> opt)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input!\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (opt == 1) {
        cout << "Enter Customer ID: ";
        int id;
        if (!(cin >> id)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid ID!\n";
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int idx = findCustomerIndex(id);
        if (idx == -1) {
            cout << "Customer with ID " << id << " not found!\n";
        } else {
            cout << "\nCustomer Found:\n";
            customers[idx].display();
        }
    } else if (opt == 2) {
        cout << "Enter search keyword for Name: ";
        string query;
        getline(cin, query);
        string lowerQuery = toLowerStr(query);

        bool found = false;
        cout << "\n--- SEARCH RESULTS ---" << endl;
        for (int i = 0; i < customerCount; i++) {
            string lowerName = toLowerStr(customers[i].getName());
            if (lowerName.find(lowerQuery) != string::npos) {
                customers[i].display();
                cout << "------------------------------------------------------------------------" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No customer matched \"" << query << "\".\n";
        }
    } else {
        cout << "Invalid option!\n";
    }
}

// Update fields of an existing Customer
void Restaurant::updateCustomer() {
    if (customerCount == 0) {
        cout << "\nNo customers to update.\n";
        return;
    }
    cout << "Enter Customer ID to update: ";
    int id;
    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID!\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int idx = findCustomerIndex(id);
    if (idx == -1) {
        cout << "Customer with ID " << id << " not found!\n";
        return;
    }

    cout << "\nCurrent Details:\n";
    customers[idx].display();

    cout << "\nWhat would you like to update?\n";
    cout << "1. Name\n2. Phone\n3. Address\nEnter choice: ";
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice!\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (choice) {
        case 1: {
            cout << "Enter new Name: ";
            string newName;
            getline(cin, newName);
            if (!newName.empty()) {
                customers[idx].setName(newName);
                cout << "Customer name updated successfully!\n";
            } else {
                cout << "Name cannot be empty!\n";
            }
            break;
        }
        case 2: {
            cout << "Enter new 10-digit Phone: ";
            string newPhone;
            getline(cin, newPhone);
            if (isValidPhoneNumber(newPhone)) {
                customers[idx].setPhone(newPhone);
                cout << "Phone updated successfully!\n";
            } else {
                cout << "Invalid phone number! Must be 10 digits.\n";
            }
            break;
        }
        case 3: {
            cout << "Enter new Address: ";
            string newAddr;
            getline(cin, newAddr);
            customers[idx].setAddress(newAddr);
            cout << "Address updated successfully!\n";
            break;
        }
        default:
            cout << "Invalid choice!\n";
            break;
    }
}

// Delete Customer and shift array
void Restaurant::deleteCustomer() {
    if (customerCount == 0) {
        cout << "\nNo customers to delete.\n";
        return;
    }
    cout << "Enter Customer ID to delete: ";
    int id;
    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID!\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int idx = findCustomerIndex(id);
    if (idx == -1) {
        cout << "Customer with ID " << id << " not found!\n";
        return;
    }

    cout << "Are you sure you want to delete customer '" << customers[idx].getName() << "'? (y/n): ";
    char confirm;
    cin >> confirm;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (confirm == 'y' || confirm == 'Y') {
        for (int i = idx; i < customerCount - 1; i++) {
            customers[i] = customers[i + 1];
        }
        customerCount--;
        cout << "Customer deleted successfully!\n";
    } else {
        cout << "Deletion cancelled.\n";
    }
}

// Display Orders with Customer Name and Menu Item Names looked up
void Restaurant::displayOrders() const {
    if (orderCount == 0) {
        cout << "\nNo orders found.\n";
        return;
    }
    cout << "\n================================ ORDERS ================================" << endl;
    for (int i = 0; i < orderCount; i++) {
        orders[i].display();
        int cIdx = findCustomerIndex(orders[i].getCustomerId());
        string cName = (cIdx != -1) ? customers[cIdx].getName() : "Unknown Customer";
        cout << "Customer Name : " << cName << endl;
        cout << "Order Items Detail:" << endl;
        for (int j = 0; j < orders[i].getItemCount(); j++) {
            int itemId = orders[i].getItemId(j);
            int qty = orders[i].getQuantity(j);
            int mIdx = findMenuItemIndex(itemId);
            string iName = (mIdx != -1) ? menuItems[mIdx]->getName() : "Unknown Item";
            double iPrice = (mIdx != -1) ? menuItems[mIdx]->getPrice() : 0.0;
            cout << "  - " << iName << " (ID: " << itemId << ") x " << qty 
                 << " @ Rs. " << fixed << setprecision(2) << iPrice 
                 << " = Rs. " << (iPrice * qty) << endl;
        }
        cout << "------------------------------------------------------------------------" << endl;
    }
}

// Search Order by Order ID or Customer ID
void Restaurant::searchOrder() const {
    if (orderCount == 0) {
        cout << "\nNo orders to search.\n";
        return;
    }
    cout << "\n--- SEARCH ORDER ---" << endl;
    cout << "1. Search by Order ID\n2. Search by Customer ID\nEnter choice: ";
    int opt;
    if (!(cin >> opt)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice!\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (opt == 1) {
        cout << "Enter Order ID: ";
        int oid;
        if (!(cin >> oid)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Order ID!\n";
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int idx = findOrderIndex(oid);
        if (idx == -1) {
            cout << "Order #" << oid << " not found!\n";
        } else {
            cout << "\nOrder Found:\n";
            orders[idx].display();
            int cIdx = findCustomerIndex(orders[idx].getCustomerId());
            cout << "Customer Name : " << (cIdx != -1 ? customers[cIdx].getName() : "Unknown") << endl;
        }
    } else if (opt == 2) {
        cout << "Enter Customer ID: ";
        int cid;
        if (!(cin >> cid)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Customer ID!\n";
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        bool found = false;
        cout << "\n--- ORDERS FOR CUSTOMER #" << cid << " ---" << endl;
        for (int i = 0; i < orderCount; i++) {
            if (orders[i].getCustomerId() == cid) {
                orders[i].display();
                cout << "------------------------------------------------------------------------" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No orders found for Customer #" << cid << ".\n";
        }
    } else {
        cout << "Invalid choice!\n";
    }
}

// Update Order status
void Restaurant::updateOrderStatus() {
    if (orderCount == 0) {
        cout << "\nNo orders to update.\n";
        return;
    }
    cout << "Enter Order ID to update: ";
    int oid;
    if (!(cin >> oid)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid Order ID!\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int idx = findOrderIndex(oid);
    if (idx == -1) {
        cout << "Order #" << oid << " not found!\n";
        return;
    }

    cout << "Current Status: " << orders[idx].getStatus() << endl;
    cout << "Select New Status:\n1. Pending\n2. Completed\n3. Cancelled\nEnter choice: ";
    int stChoice;
    if (!(cin >> stChoice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input!\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (stChoice) {
        case 1: orders[idx].setStatus("Pending"); break;
        case 2: orders[idx].setStatus("Completed"); break;
        case 3: orders[idx].setStatus("Cancelled"); break;
        default: cout << "Invalid status choice! No changes made.\n"; return;
    }
    cout << "Order status updated to '" << orders[idx].getStatus() << "' successfully!\n";
}

// Delete Order and shift array
void Restaurant::deleteOrder() {
    if (orderCount == 0) {
        cout << "\nNo orders to delete.\n";
        return;
    }
    cout << "Enter Order ID to delete: ";
    int oid;
    if (!(cin >> oid)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid Order ID!\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int idx = findOrderIndex(oid);
    if (idx == -1) {
        cout << "Order #" << oid << " not found!\n";
        return;
    }

    cout << "Are you sure you want to delete Order #" << oid << "? (y/n): ";
    char confirm;
    cin >> confirm;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (confirm == 'y' || confirm == 'Y') {
        for (int i = idx; i < orderCount - 1; i++) {
            orders[i] = orders[i + 1];
        }
        orderCount--;
        cout << "Order #" << oid << " deleted successfully!\n";
    } else {
        cout << "Deletion cancelled.\n";
    }
}

// Display all Bills
void Restaurant::displayBills() const {
    if (billCount == 0) {
        cout << "\nNo bills found.\n";
        return;
    }
    cout << "\n================================ BILLS ================================" << endl;
    for (int i = 0; i < billCount; i++) {
        bills[i].display();
        cout << "------------------------------------------------------------------------" << endl;
    }
}

// Search Bill by Bill ID or Order ID
void Restaurant::searchBill() const {
    if (billCount == 0) {
        cout << "\nNo bills to search.\n";
        return;
    }
    cout << "\n--- SEARCH BILL ---" << endl;
    cout << "1. Search by Bill ID\n2. Search by Order ID\nEnter choice: ";
    int opt;
    if (!(cin >> opt)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input!\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (opt == 1) {
        cout << "Enter Bill ID: ";
        int bid;
        if (!(cin >> bid)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Bill ID!\n";
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int idx = findBillIndex(bid);
        if (idx == -1) {
            cout << "Bill #" << bid << " not found!\n";
        } else {
            cout << "\nBill Found:\n";
            bills[idx].display();
        }
    } else if (opt == 2) {
        cout << "Enter Order ID: ";
        int oid;
        if (!(cin >> oid)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Order ID!\n";
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        bool found = false;
        cout << "\n--- BILLS FOR ORDER #" << oid << " ---" << endl;
        for (int i = 0; i < billCount; i++) {
            if (bills[i].getOrderId() == oid) {
                bills[i].display();
                cout << "------------------------------------------------------------------------" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No bills found for Order #" << oid << ".\n";
        }
    } else {
        cout << "Invalid choice!\n";
    }
}

// Place Order - Main Transaction workflow
void Restaurant::placeOrder() {
    cout << "\n========================================================" << endl;
    cout << "              PLACE ORDER (MAIN TRANSACTION)            " << endl;
    cout << "========================================================" << endl;

    if (menuCount == 0) {
        cout << "Cannot place order: No menu items available in the system!\n";
        cout << "Please add menu items first.\n";
        return;
    }

    // Step 1: Customer Selection or Creation
    cout << "\n--- Step 1: Customer Selection ---" << endl;
    cout << "1. Select Existing Customer\n2. Register New Customer\nEnter choice: ";
    int custChoice;
    if (!(cin >> custChoice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Transaction cancelled.\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int selectedCustomerId = -1;
    if (custChoice == 1) {
        if (customerCount == 0) {
            cout << "No customers exist yet! Registering a new customer...\n";
            addCustomer();
            if (customerCount > 0) {
                selectedCustomerId = customers[customerCount - 1].getCustomerId();
            } else {
                cout << "Customer registration failed. Transaction cancelled.\n";
                return;
            }
        } else {
            displayCustomers();
            cout << "Enter Customer ID to place order for: ";
            int cid;
            if (!(cin >> cid)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid Customer ID! Transaction cancelled.\n";
                return;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            int cIdx = findCustomerIndex(cid);
            if (cIdx == -1) {
                cout << "Customer ID " << cid << " not found! Transaction cancelled.\n";
                return;
            }
            selectedCustomerId = cid;
        }
    } else if (custChoice == 2) {
        addCustomer();
        if (customerCount > 0) {
            selectedCustomerId = customers[customerCount - 1].getCustomerId();
        } else {
            cout << "Customer registration failed. Transaction cancelled.\n";
            return;
        }
    } else {
        cout << "Invalid choice! Transaction cancelled.\n";
        return;
    }

    // Step 2: Display Menu Items
    cout << "\n--- Step 2: Available Menu Items ---" << endl;
    displayMenuItems();

    // Step 3: Create Order object and add items
    int orderId = getNextOrderId();
    Order newOrder(orderId, selectedCustomerId);

    cout << "\n--- Step 3: Add Items to Order ---" << endl;
    bool addingItems = true;
    while (addingItems) {
        cout << "Enter Menu Item ID to add: ";
        int itemId;
        if (!(cin >> itemId)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid item ID!\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int mIdx = findMenuItemIndex(itemId);
        if (mIdx == -1) {
            cout << "Error: Menu Item with ID " << itemId << " does not exist!\n";
        } else if (!menuItems[mIdx]->isAvailable()) {
            cout << "Error: '" << menuItems[mIdx]->getName() << "' is currently not available!\n";
        } else {
            cout << "Enter quantity for '" << menuItems[mIdx]->getName() << "': ";
            int qty;
            if (!(cin >> qty) || qty <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Error: Quantity must be a positive integer!\n";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                newOrder.addItem(itemId, qty);
                cout << "Added " << qty << "x '" << menuItems[mIdx]->getName() 
                     << "' (@ Rs. " << menuItems[mIdx]->getPrice() << " each) to order.\n";
            }
        }

        cout << "Add another item? (y/n): ";
        char more;
        cin >> more;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (more != 'y' && more != 'Y') {
            addingItems = false;
        }
    }

    if (newOrder.getItemCount() == 0) {
        cout << "\nNo items were added. Order placement cancelled.\n";
        return;
    }

    // Step 4: Calculate subtotal and display order summary
    cout << "\n--- Step 4: Order Summary ---" << endl;
    double subtotal = 0.0;
    cout << "Order ID    : " << orderId << endl;
    cout << "Customer ID : " << selectedCustomerId << endl;
    cout << "Items Ordered:" << endl;
    for (int i = 0; i < newOrder.getItemCount(); i++) {
        int iId = newOrder.getItemId(i);
        int qty = newOrder.getQuantity(i);
        int mIdx = findMenuItemIndex(iId);
        string name = (mIdx != -1) ? menuItems[mIdx]->getName() : "Item";
        double price = (mIdx != -1) ? menuItems[mIdx]->getPrice() : 0.0;
        double lineTotal = price * qty;
        subtotal += lineTotal;
        cout << "  - " << left << setw(20) << name 
             << " Qty: " << setw(3) << qty 
             << " Rate: Rs. " << setw(7) << fixed << setprecision(2) << price 
             << " Line Total: Rs. " << lineTotal << endl;
    }
    cout << "Subtotal: Rs. " << fixed << setprecision(2) << subtotal << endl;

    // Step 5: Tax and Discount
    cout << "\n--- Step 5: Tax & Discount ---" << endl;
    double taxRate = 18.0;  // Default 18% GST
    cout << "Standard Tax Rate is 18.0% (GST). Enter custom rate or press Enter to keep 18%: ";
    string taxInput;
    getline(cin, taxInput);
    if (!taxInput.empty()) {
        try {
            double customRate = stod(taxInput);
            if (customRate >= 0.0) {
                taxRate = customRate;
            }
        } catch (...) {
            cout << "Invalid tax input. Keeping default 18.0%.\n";
        }
    }

    double discount = 0.0;
    cout << "Enter discount amount in Rs. (0 for none): ";
    if (cin >> discount) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (discount < 0.0) discount = 0.0;
        if (discount > subtotal) {
            cout << "Discount cannot exceed subtotal. Setting discount equal to subtotal.\n";
            discount = subtotal;
        }
    } else {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        discount = 0.0;
    }

    // Step 6: Create Bill
    int billId = getNextBillId();
    Bill newBill(billId, orderId, selectedCustomerId, subtotal, taxRate, discount);
    newBill.calculateTotal();

    cout << "\n--- Step 6: Generated Bill ---" << endl;
    newBill.display();

    // Step 7: Payment
    cout << "\n--- Step 7: Payment Processing ---" << endl;
    cout << "Select Payment Method:\n1. Cash\n2. Card\n3. UPI\nEnter choice: ";
    int payChoice;
    string method = "Cash";
    if (cin >> payChoice) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (payChoice == 2) method = "Card";
        else if (payChoice == 3) method = "UPI";
        else method = "Cash";
    } else {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        method = "Cash";
    }

    newBill.setPaymentMethod(method);
    newBill.setPaymentStatus("Paid");
    newOrder.setStatus("Completed");

    // Store in arrays
    if (orderCount >= orderCapacity) {
        resizeOrders();
    }
    orders[orderCount++] = newOrder;

    if (billCount >= billCapacity) {
        resizeBills();
    }
    bills[billCount++] = newBill;

    cout << "\n========================================================" << endl;
    cout << "  PAYMENT SUCCESSFUL! ORDER & BILL COMPLETED" << endl;
    cout << "  Order #" << orderId << " | Bill #" << billId 
         << " | Paid via " << method << endl;
    cout << "========================================================" << endl;
}

// Generate statistical and financial report
void Restaurant::generateReport() const {
    cout << "\n========================================" << endl;
    cout << "          RESTAURANT REPORT             " << endl;
    cout << "========================================" << endl;
    cout << "Total Menu Items : " << menuCount << endl;
    cout << "Total Customers  : " << customerCount << endl;
    cout << "Total Orders     : " << orderCount << endl;
    cout << "Total Bills      : " << billCount << endl;

    int pendingOrders = 0;
    int completedOrders = 0;
    int cancelledOrders = 0;

    for (int i = 0; i < orderCount; i++) {
        string s = orders[i].getStatus();
        if (s == "Pending") pendingOrders++;
        else if (s == "Completed") completedOrders++;
        else if (s == "Cancelled") cancelledOrders++;
    }

    cout << "\n--- Order Summary ---" << endl;
    cout << "Pending Orders   : " << pendingOrders << endl;
    cout << "Completed Orders : " << completedOrders << endl;
    cout << "Cancelled Orders : " << cancelledOrders << endl;

    double totalRevenue = 0.0;
    double totalTax = 0.0;
    double totalDiscount = 0.0;

    for (int i = 0; i < billCount; i++) {
        if (bills[i].getPaymentStatus() == "Paid") {
            totalRevenue += bills[i].getTotalAmount();
            totalTax += bills[i].getTaxAmount();
            totalDiscount += bills[i].getDiscount();
        }
    }

    cout << "\n--- Revenue Summary ---" << endl;
    cout << fixed << setprecision(2);
    cout << "Total Revenue        : Rs. " << totalRevenue << endl;
    cout << "Total Tax Collected  : Rs. " << totalTax << endl;
    cout << "Total Discounts Given: Rs. " << totalDiscount << endl;

    cout << "\n--- Popular Items ---" << endl;
    // Map item IDs to total ordered quantities
    struct ItemTally {
        int itemId;
        int totalQuantity;
    };
    vector<ItemTally> tallies;

    for (int i = 0; i < orderCount; i++) {
        for (int j = 0; j < orders[i].getItemCount(); j++) {
            int iId = orders[i].getItemId(j);
            int qty = orders[i].getQuantity(j);

            bool found = false;
            for (auto& t : tallies) {
                if (t.itemId == iId) {
                    t.totalQuantity += qty;
                    found = true;
                    break;
                }
            }
            if (!found) {
                tallies.push_back({iId, qty});
            }
        }
    }

    // Sort tallies descending by total quantity
    sort(tallies.begin(), tallies.end(), [](const ItemTally& a, const ItemTally& b) {
        return a.totalQuantity > b.totalQuantity;
    });

    if (tallies.empty()) {
        cout << "No items have been ordered yet." << endl;
    } else {
        int topN = min((int)tallies.size(), 3);
        for (int k = 0; k < topN; k++) {
            int mIdx = findMenuItemIndex(tallies[k].itemId);
            string name = (mIdx != -1) ? menuItems[mIdx]->getName() : "Item #" + to_string(tallies[k].itemId);
            cout << (k + 1) << ". " << name << " - " << tallies[k].totalQuantity << " orders" << endl;
        }
    }
    cout << "========================================" << endl;
}

// Save all system data to text files
void Restaurant::saveData() {
    try {
        fileManager.saveMenuItems(menuItems, menuCount, dataPath + "menu_items.txt");
        fileManager.saveCustomers(customers, customerCount, dataPath + "customers.txt");
        fileManager.saveOrders(orders, orderCount, dataPath + "orders.txt");
        fileManager.saveBills(bills, billCount, dataPath + "bills.txt");
        cout << "\nAll data saved successfully!\n";
    } catch (const exception& e) {
        cout << "Error saving data: " << e.what() << endl;
    }
}

// Load all system data from text files
void Restaurant::loadData() {
    try {
        // Free existing dynamic memory first
        for (int i = 0; i < menuCount; i++) {
            delete menuItems[i];
        }
        delete[] menuItems;
        delete[] customers;
        delete[] orders;
        delete[] bills;

        menuCapacity = 10;
        customerCapacity = 10;
        orderCapacity = 10;
        billCapacity = 10;

        menuItems = new MenuItem*[menuCapacity];
        customers = new Customer[customerCapacity];
        orders = new Order[orderCapacity];
        bills = new Bill[billCapacity];

        for (int i = 0; i < menuCapacity; i++) {
            menuItems[i] = nullptr;
        }

        menuCount = fileManager.loadMenuItems(menuItems, menuCapacity, dataPath + "menu_items.txt");
        customerCount = fileManager.loadCustomers(customers, customerCapacity, dataPath + "customers.txt");
        orderCount = fileManager.loadOrders(orders, orderCapacity, dataPath + "orders.txt");
        billCount = fileManager.loadBills(bills, billCapacity, dataPath + "bills.txt");

        cout << "\nData loaded: " << menuCount << " menu items, " << customerCount
             << " customers, " << orderCount << " orders, " << billCount << " bills.\n";
    } catch (const exception& e) {
        cout << "Error loading data: " << e.what() << endl;
    }
}
