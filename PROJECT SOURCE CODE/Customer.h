#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <iostream>

using namespace std;

class Customer {
private:
    int customerId;
    string name;
    string phone;
    string address;

public:
    Customer();
    Customer(int customerId, const string& name, const string& phone, const string& address);
    ~Customer();

    // Getters
    int getCustomerId() const;
    string getName() const;
    string getPhone() const;
    string getAddress() const;

    // Setters
    void setCustomerId(int id);
    void setName(const string& n);
    void setPhone(const string& p);
    void setAddress(const string& a);

    void display() const;
    string toFileString() const;
    void fromFileString(const string& line);
};

#endif // CUSTOMER_H
