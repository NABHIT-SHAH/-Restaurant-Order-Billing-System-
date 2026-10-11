============================================
  RESTAURANT ORDER & BILLING SYSTEM
============================================

Student Information:
  Enrollment Number : IU2541230417
  Project Code      : CPP07
  Project Name      : Restaurant Order & Billing System

============================================
PROJECT DESCRIPTION
============================================
A console-based Restaurant Order and Billing System built in C++
demonstrating core OOP concepts including classes, encapsulation,
inheritance, runtime polymorphism, dynamic memory management,
file handling, and exception handling.

============================================
FOLDER STRUCTURE
============================================
  Source/       - All .h and .cpp source files
  Data/         - Data files (menu_items.txt, customers.txt, orders.txt, bills.txt)
  Diagrams/     - UML diagrams (UseCase, ClassDiagram, Sequence1, Sequence2)
  Executable/   - Compiled executable (Project)
  Screenshots/  - Program screenshots
  README.txt    - This file
  ProjectReport.pdf - Project report

============================================
HOW TO COMPILE
============================================
Option 1: Using Makefile
  cd to project root directory
  make
  ./Executable/Project

Option 2: Manual compilation
  g++ -std=c++17 -o Executable/Project Source/*.cpp
  ./Executable/Project

============================================
HOW TO USE
============================================
1. Run the executable from the project root directory
2. The system will automatically load saved data if available
3. Use the menu to:
   - Add/Display/Search/Update/Delete menu items and customers
   - Place orders (Main Transaction)
   - Generate reports
   - Save/Load data
4. Data is automatically saved when you exit

============================================
CLASSES
============================================
1. MenuItem    - Base class for menu items (polymorphic)
2. FoodItem    - Derived from MenuItem (food items with cuisine type)
3. BeverageItem- Derived from MenuItem (beverages with size)
4. Customer    - Customer information
5. Order       - Order with dynamic arrays for items/quantities
6. Bill        - Billing with tax, discount, payment
7. Restaurant  - Main system class managing all operations
8. FileManager - File I/O handler for data persistence

============================================
OOP CONCEPTS DEMONSTRATED
============================================
- Classes and Objects
- Encapsulation (private data, public interface)
- Default and Parameterized Constructors
- Destructors
- Inheritance (FoodItem, BeverageItem extend MenuItem)
- Runtime Polymorphism (virtual functions, base class pointers)
- Dynamic Memory Management (new/delete for arrays)
- File Handling (save/load to text files)
- Exception Handling (try-catch blocks)
- Input Validation

============================================
DATA FILES
============================================
All data is stored in the Data/ folder:
  - menu_items.txt  : Menu item records
  - customers.txt   : Customer records
  - orders.txt      : Order records
  - bills.txt       : Bill records

Files use pipe '|' as delimiter.
