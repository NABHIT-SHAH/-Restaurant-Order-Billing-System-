#ifndef BILL_H
#define BILL_H

#include <string>
#include <iostream>

using namespace std;

class Bill {
private:
    int billId;
    int orderId;
    int customerId;
    double subtotal;
    double taxRate;       // as percentage, e.g., 18.0 for 18%
    double taxAmount;
    double discount;      // flat discount amount
    double totalAmount;
    string paymentStatus; // Unpaid, Paid
    string paymentMethod; // Cash, Card, UPI
    string billDate;

public:
    Bill();
    Bill(int billId, int orderId, int customerId, double subtotal,
         double taxRate, double discount);
    ~Bill();

    // Getters
    int getBillId() const;
    int getOrderId() const;
    int getCustomerId() const;
    double getSubtotal() const;
    double getTaxRate() const;
    double getTaxAmount() const;
    double getDiscount() const;
    double getTotalAmount() const;
    string getPaymentStatus() const;
    string getPaymentMethod() const;
    string getBillDate() const;

    // Setters
    void setBillId(int id);
    void setOrderId(int id);
    void setCustomerId(int id);
    void setSubtotal(double amt);
    void setTaxRate(double rate);
    void setDiscount(double disc);
    void setPaymentStatus(const string& s);
    void setPaymentMethod(const string& m);
    void setBillDate(const string& d);

    void calculateTotal();
    void display() const;
    string toFileString() const;
    void fromFileString(const string& line);
};

#endif
