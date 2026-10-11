#include "Order.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstdio>

using namespace std;

// Default constructor
Order::Order()
    : orderId(0), customerId(0), itemCount(0), capacity(5),
      status("Pending"), orderDate("") {
    itemIds = new int[capacity];
    quantities = new int[capacity];
}

// Parameterized constructor
Order::Order(int orderId, int customerId)
    : orderId(orderId), customerId(customerId), itemCount(0), capacity(5),
      status("Pending") {
    // Current date formatted as YYYY-MM-DD
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buf[11];
    snprintf(buf, sizeof(buf), "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
    orderDate = string(buf);

    itemIds = new int[capacity];
    quantities = new int[capacity];
}

// Copy constructor (Rule of Three) - deep copy
Order::Order(const Order& other)
    : orderId(other.orderId), customerId(other.customerId),
      itemCount(other.itemCount), capacity(other.capacity),
      status(other.status), orderDate(other.orderDate) {
    itemIds = new int[capacity];
    quantities = new int[capacity];
    for (int i = 0; i < itemCount; i++) {
        itemIds[i] = other.itemIds[i];
        quantities[i] = other.quantities[i];
    }
}

// Copy assignment operator (Rule of Three) - deep copy
Order& Order::operator=(const Order& other) {
    if (this != &other) {
        delete[] itemIds;
        delete[] quantities;

        orderId = other.orderId;
        customerId = other.customerId;
        itemCount = other.itemCount;
        capacity = other.capacity;
        status = other.status;
        orderDate = other.orderDate;

        itemIds = new int[capacity];
        quantities = new int[capacity];
        for (int i = 0; i < itemCount; i++) {
            itemIds[i] = other.itemIds[i];
            quantities[i] = other.quantities[i];
        }
    }
    return *this;
}

// Destructor - frees dynamically allocated arrays
Order::~Order() {
    delete[] itemIds;
    delete[] quantities;
}

// Private helper to double dynamic array capacity
void Order::resize() {
    int newCapacity = capacity * 2;
    int* newItemIds = new int[newCapacity];
    int* newQuantities = new int[newCapacity];

    for (int i = 0; i < itemCount; i++) {
        newItemIds[i] = itemIds[i];
        newQuantities[i] = quantities[i];
    }

    delete[] itemIds;
    delete[] quantities;

    itemIds = newItemIds;
    quantities = newQuantities;
    capacity = newCapacity;
}

// Getters
int Order::getOrderId() const {
    return orderId;
}

int Order::getCustomerId() const {
    return customerId;
}

int Order::getItemCount() const {
    return itemCount;
}

int Order::getItemId(int index) const {
    if (index >= 0 && index < itemCount) {
        return itemIds[index];
    }
    return -1;
}

int Order::getQuantity(int index) const {
    if (index >= 0 && index < itemCount) {
        return quantities[index];
    }
    return 0;
}

string Order::getStatus() const {
    return status;
}

string Order::getOrderDate() const {
    return orderDate;
}

// Setters
void Order::setOrderId(int id) {
    orderId = id;
}

void Order::setCustomerId(int id) {
    customerId = id;
}

void Order::setStatus(const string& s) {
    status = s;
}

void Order::setOrderDate(const string& d) {
    orderDate = d;
}

// Add item or increment quantity if already present
void Order::addItem(int itemId, int quantity) {
    if (quantity <= 0) {
        return;
    }

    // Check if item already exists
    for (int i = 0; i < itemCount; i++) {
        if (itemIds[i] == itemId) {
            quantities[i] += quantity;
            return;
        }
    }

    // Expand array if full
    if (itemCount >= capacity) {
        resize();
    }

    itemIds[itemCount] = itemId;
    quantities[itemCount] = quantity;
    itemCount++;
}

// Remove item and shift subsequent elements left
void Order::removeItem(int itemId) {
    int targetIndex = -1;
    for (int i = 0; i < itemCount; i++) {
        if (itemIds[i] == itemId) {
            targetIndex = i;
            break;
        }
    }

    if (targetIndex != -1) {
        for (int i = targetIndex; i < itemCount - 1; i++) {
            itemIds[i] = itemIds[i + 1];
            quantities[i] = quantities[i + 1];
        }
        itemCount--;
    }
}

// Display order details and list of items
void Order::display() const {
    cout << "Order #" << orderId << " | Customer: " << customerId
         << " | Date: " << orderDate << " | Status: " << status << endl;
    cout << "Items:" << endl;
    for (int i = 0; i < itemCount; i++) {
        cout << "  Item ID: " << itemIds[i] << ", Qty: " << quantities[i] << endl;
    }
}

// Serialize order to pipe-delimited format with comma-separated item pairs
string Order::toFileString() const {
    stringstream ss;
    ss << orderId << "|" << customerId << "|" << status << "|" << orderDate << "|" << itemCount << "|";
    for (int i = 0; i < itemCount; i++) {
        ss << itemIds[i] << ":" << quantities[i];
        if (i < itemCount - 1) {
            ss << ",";
        }
    }
    return ss.str();
}

// Deserialize order from pipe-delimited string
void Order::fromFileString(const string& line) {
    stringstream ss(line);
    string token;

    if (getline(ss, token, '|')) orderId = stoi(token);
    if (getline(ss, token, '|')) customerId = stoi(token);
    if (getline(ss, token, '|')) status = token;
    if (getline(ss, token, '|')) orderDate = token;

    int count = 0;
    if (getline(ss, token, '|')) {
        count = stoi(token);
    }

    // Reset dynamic arrays with appropriate capacity
    delete[] itemIds;
    delete[] quantities;

    capacity = (count > 5) ? count * 2 : 5;
    itemIds = new int[capacity];
    quantities = new int[capacity];
    itemCount = 0;

    string itemsToken;
    if (getline(ss, itemsToken)) {
        if (!itemsToken.empty()) {
            stringstream itemStream(itemsToken);
            string pairToken;
            while (getline(itemStream, pairToken, ',')) {
                if (pairToken.empty()) continue;
                size_t colonPos = pairToken.find(':');
                if (colonPos != string::npos) {
                    int id = stoi(pairToken.substr(0, colonPos));
                    int qty = stoi(pairToken.substr(colonPos + 1));
                    itemIds[itemCount] = id;
                    quantities[itemCount] = qty;
                    itemCount++;
                }
            }
        }
    }
}
