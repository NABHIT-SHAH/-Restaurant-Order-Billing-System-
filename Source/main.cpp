// Restaurant Order & Billing System
// Enrollment: IU2541230417 | Project Code: CPP07
// Main entry point - creates system object and runs the application

#include <iostream>
#include "Restaurant.h"

using namespace std;

int main() {
    cout << "============================================" << endl;
    cout << "   RESTAURANT ORDER & BILLING SYSTEM" << endl;
    cout << "   Enrollment No: IU2541230417" << endl;
    cout << "   Project Code : CPP07" << endl;
    cout << "============================================" << endl;

    try {
        Restaurant restaurant;
        restaurant.run();
    } catch (const exception& e) {
        cerr << "Fatal error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
