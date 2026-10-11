# Restaurant Order & Billing System
# Enrollment: IU2541230417 | Project Code: CPP07

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
SRC_DIR = Source
OBJ_DIR = obj
BIN_DIR = Executable
DATA_DIR = Data

SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/MenuItem.cpp $(SRC_DIR)/FoodItem.cpp \
       $(SRC_DIR)/BeverageItem.cpp $(SRC_DIR)/Customer.cpp $(SRC_DIR)/Order.cpp \
       $(SRC_DIR)/Bill.cpp $(SRC_DIR)/FileManager.cpp $(SRC_DIR)/Restaurant.cpp

TARGET = $(BIN_DIR)/Project

.PHONY: all clean dirs

all: dirs $(TARGET)

dirs:
	mkdir -p $(BIN_DIR) $(DATA_DIR) $(OBJ_DIR)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

run: all
	./$(TARGET)
