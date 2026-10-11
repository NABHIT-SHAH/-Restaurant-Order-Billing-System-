#include "Bill.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstdio>

using namespace std;

// Default constructor
Bill::Bill()
    : billId(0), orderId(0), customerId(0), subtotal(0.0),
      taxRate(0.0), taxAmount(0.0), discount(0.0), totalAmount(0.0),
      paymentStatus("Unpaid"), paymentMethod(""), billDate("") {
}

// Parameterized constructor
Bill::Bill(int billId, int orderId, int customerId, double subtotal,
           double taxRate, double discount)
    : billId(billId), orderId(orderId), customerId(customerId),
      subtotal(subtotal), taxRate(taxRate), discount(discount),
      paymentStatus("Unpaid"), paymentMethod("") {
    // Current date formatted as YYYY-MM-DD
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buf[11];
    snprintf(buf, sizeof(buf), "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
    billDate = string(buf);

    calculateTotal();
}

// Destructor
Bill::~Bill() {
}

// Getters
int Bill::getBillId() const {
    return billId;
}

int Bill::getOrderId() const {
    return orderId;
}

int Bill::getCustomerId() const {
    return customerId;
}

double Bill::getSubtotal() const {
    return subtotal;
}

double Bill::getTaxRate() const {
    return taxRate;
}

double Bill::getTaxAmount() const {
    return taxAmount;
}

double Bill::getDiscount() const {
    return discount;
}

double Bill::getTotalAmount() const {
    return totalAmount;
}

string Bill::getPaymentStatus() const {
    return paymentStatus;
}

string Bill::getPaymentMethod() const {
    return paymentMethod;
}

string Bill::getBillDate() const {
    return billDate;
}

// Setters
void Bill::setBillId(int id) {
    billId = id;
}

void Bill::setOrderId(int id) {
    orderId = id;
}

void Bill::setCustomerId(int id) {
    customerId = id;
}

void Bill::setSubtotal(double amt) {
    subtotal = amt;
}

void Bill::setTaxRate(double rate) {
    taxRate = rate;
}

void Bill::setDiscount(double disc) {
    discount = disc;
}

void Bill::setPaymentStatus(const string& s) {
    paymentStatus = s;
}

void Bill::setPaymentMethod(const string& m) {
    paymentMethod = m;
}

void Bill::setBillDate(const string& d) {
    billDate = d;
}

// Compute tax and total amounts
void Bill::calculateTotal() {
    taxAmount = subtotal * taxRate / 100.0;
    totalAmount = subtotal + taxAmount - discount;
}

// Display bill receipt in formatted view
void Bill::display() const {
    cout << "============================================" << endl;
    cout << "         RESTAURANT BILL" << endl;
    cout << "============================================" << endl;
    cout << "Bill ID    : " << billId << endl;
    cout << "Order ID   : " << orderId << endl;
    cout << "Customer ID: " << customerId << endl;
    cout << "Date       : " << billDate << endl;
    cout << "--------------------------------------------" << endl;
    cout << fixed << setprecision(2);
    cout << "Subtotal   : Rs. " << subtotal << endl;
    cout << "Tax (" << taxRate << "%): Rs. " << taxAmount << endl;
    cout << "Discount   : Rs. " << discount << endl;
    cout << "--------------------------------------------" << endl;
    cout << "TOTAL      : Rs. " << totalAmount << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Payment    : " << paymentStatus;
    if (!paymentMethod.empty()) {
        cout << " (" << paymentMethod << ")";
    }
    cout << endl;
    cout << "============================================" << endl;
}

// Serialize bill to pipe-delimited format
string Bill::toFileString() const {
    stringstream ss;
    ss << fixed << setprecision(2);
    ss << billId << "|" << orderId << "|" << customerId << "|"
       << subtotal << "|" << taxRate << "|" << taxAmount << "|"
       << discount << "|" << totalAmount << "|" << paymentStatus << "|"
       << paymentMethod << "|" << billDate;
    return ss.str();
}

// Deserialize bill from pipe-delimited string
void Bill::fromFileString(const string& line) {
    stringstream ss(line);
    string token;

    if (getline(ss, token, '|')) billId = stoi(token);
    if (getline(ss, token, '|')) orderId = stoi(token);
    if (getline(ss, token, '|')) customerId = stoi(token);
    if (getline(ss, token, '|')) subtotal = stod(token);
    if (getline(ss, token, '|')) taxRate = stod(token);
    if (getline(ss, token, '|')) taxAmount = stod(token);
    if (getline(ss, token, '|')) discount = stod(token);
    if (getline(ss, token, '|')) totalAmount = stod(token);
    if (getline(ss, token, '|')) paymentStatus = token;
    if (getline(ss, token, '|')) paymentMethod = token;
    if (getline(ss, token, '|')) billDate = token;
}
