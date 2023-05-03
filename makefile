DEBUG = -g
CPP = g++
CXXFLAGS = -Wall -Wextra -O -std=c++17 -Ivendor/boost_1_81_0 -Iinclude -Wno-deprecated-declarations
CFLAGS = -Wall -Wextra -O -std=c11
BUILD_DIR = build
SRC_DIR = src
INC_DIR = include

$(BUILD_DIR)/airedale: $(BUILD_DIR)/vcppwd.o $(BUILD_DIR)/main.o
	$(CPP) $(DEBUG) $(CXXFLAGS) -o airedale $(BUILD_DIR)/vcppwd.o $(BUILD_DIR)/main.o

main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/getpass.h
	$(CPP) $(DEBUG) $(CXXFLAGS) -c $(SRC_DIR)/main.cpp

vcppwd.o: $(SRC_DIR)/vcppwd.cpp $(INC_DIR)/vcppwd.hpp
	$(CPP) $(DEBUG) $(CXXFLAGS) -c $(SRC_DIR)/vcppwd.cpp

getpass.o: $(SRC_DIR)/getpass.c
	$(CC) $(DEBUG) $(CFLAGS) -c $(SRC_DIR)/getpass.c

clean:
	rm -f $(BUILD_DIR)/main.o $(BUILD_DIR)/vcppwd.o $(BUILD_DIR)/airedale