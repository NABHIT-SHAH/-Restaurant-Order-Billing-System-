#include "Customer.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

// Default constructor
Customer::Customer()
    : customerId(0), name(""), phone(""), address("") {}

// Parameterized constructor
Customer::Customer(int customerId, const string& name, const string& phone, const string& address)
    : customerId(customerId), name(name), phone(phone), address(address) {}

// Destructor
Customer::~Customer() {
    // Empty body
}

// Getters
int Customer::getCustomerId() const {
    return customerId;
}

string Customer::getName() const {
    return name;
}

string Customer::getPhone() const {
    return phone;
}

string Customer::getAddress() const {
    return address;
}

// Setters
void Customer::setCustomerId(int id) {
    customerId = id;
}

void Customer::setName(const string& n) {
    name = n;
}

void Customer::setPhone(const string& p) {
    phone = p;
}

void Customer::setAddress(const string& a) {
    address = a;
}

// Display formatted customer information
void Customer::display() const {
    cout << left << setw(6) << customerId 
         << setw(25) << name 
         << setw(15) << phone 
         << address << endl;
}

// Serializes customer data to a pipe-delimited string
string Customer::toFileString() const {
    return to_string(customerId) + "|" + name + "|" + phone + "|" + address;
}

// Deserializes customer data from a pipe-delimited string
void Customer::fromFileString(const string& line) {
    stringstream ss(line);
    string token;

    if (getline(ss, token, '|')) {
        customerId = stoi(token);
    }
    if (getline(ss, token, '|')) {
        name = token;
    }
    if (getline(ss, token, '|')) {
        phone = token;
    }
    if (getline(ss, token, '|')) {
        address = token;
    }
}
