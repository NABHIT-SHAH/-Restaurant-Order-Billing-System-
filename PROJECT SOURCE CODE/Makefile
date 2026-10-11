# Restaurant Order & Billing System
# Enrollment: IU2541230417 | Project Code: CPP07

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SRCS = main.cpp MenuItem.cpp FoodItem.cpp BeverageItem.cpp Customer.cpp \
       Order.cpp Bill.cpp FileManager.cpp Restaurant.cpp

TARGET = Project

.PHONY: all clean run

all: $(TARGET)
	cp $(TARGET) Project.exe 2>/dev/null || true

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET) Project.exe

run: all
	./$(TARGET)
