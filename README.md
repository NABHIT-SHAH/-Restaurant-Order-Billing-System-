# Restaurant Order & Billing System (CPP07)

**Student Name:** Nabhit Shah  
**Enrollment Number:** `IU2541230417`  
**Project Code:** `CPP07`  
**Course:** Object-Oriented Programming in C++ (OOPC)

---

## 📋 Project Description
A modular, object-oriented desktop console application developed in **C++17** for managing restaurant operations, dine-in table ordering, automated billing with GST and discounts, customer records, and persistent file storage.

---

## 🏗️ Architecture & Core Classes

| Class | Type | Header / Implementation | Description |
|:---|:---:|:---|:---|
| `MenuItem` | Base | `Source/MenuItem.h` / `MenuItem.cpp` | Abstract base class declaring virtual display, type identification, and file serialization methods. |
| `FoodItem` | Derived | `Source/FoodItem.h` / `FoodItem.cpp` | Extends `MenuItem` with `cuisineType` and vegetarian flag `isVeg`. |
| `BeverageItem` | Derived | `Source/BeverageItem.h` / `BeverageItem.cpp` | Extends `MenuItem` with `size` and `isHot` temperature indicator. |
| `Customer` | Entity | `Source/Customer.h` / `Customer.cpp` | Manages customer directory with 10-digit phone number validation. |
| `Order` | Entity | `Source/Order.h` / `Order.cpp` | Transaction class using **dynamic memory** (`new int[]`/`delete[]`), capacity doubling, and **Rule of Three**. |
| `Bill` | Entity | `Source/Bill.h` / `Bill.cpp` | Computes subtotal, GST (18%), discount, total, and formats customer receipts. |
| `Restaurant` | System | `Source/Restaurant.h` / `Restaurant.cpp` | Central coordinator managing dynamic arrays, 9-option interactive menu, transactions, and reports. |
| `FileManager` | Persistence | `Source/FileManager.h` / `FileManager.cpp` | Encapsulates pipe-delimited (`\|`) serialization/deserialization to and from `Data/*.txt`. |

---

## 🔑 OOP Concepts Implemented

1. **Classes and Objects:** Comprehensive modeling of domain entities.
2. **Encapsulation:** Private data members with public getters/setters.
3. **Constructors & Destructors:** Default, parameterized, and copy constructors across all classes.
4. **Inheritance:** `FoodItem` and `BeverageItem` publicly inherit from `MenuItem`.
5. **Runtime Polymorphism:** Virtual methods dispatched through dynamic pointer array `MenuItem**`.
6. **Dynamic Memory & Rule of Three:** `Order` manages dynamic arrays on heap with custom copy constructor, copy assignment operator, and destructor.
7. **File Persistence:** Flat pipe-delimited files in `Data/` automatically loaded at startup and saved on exit.
8. **Exception Handling & Validation:** `try-catch` blocks, numeric stream validation, 10-digit phone checks.

---

## 🚀 How to Compile & Run

### Using Makefile (Recommended)
```bash
# Compile
make

# Run
./Executable/Project

# Clean
make clean
```

### Manual Compilation
```bash
g++ -std=c++17 -Wall -Wextra -o Executable/Project Source/*.cpp
./Executable/Project
```

---

## 📊 Menu Operations

```
========================================
  RESTAURANT ORDER & BILLING SYSTEM
  Enrollment: IU2541230417 | CPP07
========================================
1. Add Record           (Food, Beverage, Customer)
2. Display Records      (Menu Items, Customers, Orders, Bills)
3. Search Record        (By ID or Substring Name)
4. Update Record        (Price, Availability, Customer, Order Status)
5. Delete Record        (Safe removal with array shifting)
6. Place Order          (MAIN TRANSACTION: Order + Bill + Payment)
7. Generate Report      (Revenue, GST, Discounts, Popular Items)
8. Save/Load Data       (Manual Disk Synchronization)
9. Exit                 (Auto-save on exit)
========================================
```

---

## 📁 Repository Structure

```
.
├── Source/                           # C++17 modular headers and implementations
├── Data/                             # Persisted pipe-delimited text files
├── Diagrams/                         # UML diagrams (Vector SVG)
│   ├── UseCase.svg
│   ├── ClassDiagram.svg
│   ├── Sequence1.svg                 # Main Transaction: Place Order
│   └── Sequence2.svg                 # Data Persistence Lifecycle
├── Executable/
│   └── Project                       # Compiled executable
├── Screenshots/                      # Terminal run evidence (.svg & .txt)
├── IU2541230417_CPP07_Project.zip   # Final academic submission package
├── ProjectReport.pdf                 # 8-page comprehensive report
├── ProjectReport.docx                # Microsoft Word editable report
├── README.txt                        # Plain text documentation
└── Makefile                          # Build script
```
