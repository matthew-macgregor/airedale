TARGET = airedale
BUILD_DIR = build
DEBUG = -g
CPP = c++
CXXFLAGS = -Wall -Wextra -Werror -O -std=c++17 -static
CFLAGS = -Wall -Wextra -O -std=c11 -static

SRC_DIR = src
SRC_PROVIDERS_DIR = src/providers
INC_PROVIDERS_DIR = include/providers
INC_DIR = include
INCLUDE = -I$(INC_DIR) -Ivendor/boost_1_81_0 -I vendor/libsodium/src/libsodium/include -Wno-deprecated-declarations

OBJS = $(BUILD_DIR)/policy.o \
	 $(BUILD_DIR)/main.o \
	 $(BUILD_DIR)/chacha20.o \
	 $(BUILD_DIR)/mt19937.o \
	 $(BUILD_DIR)/checksum.o \
	 $(BUILD_DIR)/util.o

LIBS = -lsodium
LIBPATH = -Lvendor/libsodium/src/libsodium/.libs

all: dir $(BUILD_DIR)/$(TARGET)

dir: $(BUILD_DIR)

clean:
	rm -f $(BUILD_DIR)/*

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CPP) -o $(BUILD_DIR)/$(TARGET) $(OBJS) $(CXXFLAGS) $(INCLUDE) $(DEBUG) $(LIBPATH) $(LIBS)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/getpass.h $(INC_DIR)/util.hpp $(INC_DIR)/providers/include.hpp $(INC_PROVIDERS_DIR)/sodium_init.hpp
	$(CPP) $(CXXFLAGS) $(DEBUG) $(INCLUDE) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/policy.o: $(SRC_DIR)/policy.cpp $(INC_DIR)/policy.hpp
	$(CPP) $(CXXFLAGS) $(DEBUG) $(INCLUDE) -c $(SRC_DIR)/policy.cpp -o $(BUILD_DIR)/policy.o

$(BUILD_DIR)/chacha20.o: $(SRC_PROVIDERS_DIR)/chacha20.cpp $(INC_PROVIDERS_DIR)/chacha20.hpp
	$(CPP) $(CXXFLAGS) $(DEBUG) $(INCLUDE) -c $(SRC_PROVIDERS_DIR)/chacha20.cpp -o $(BUILD_DIR)/chacha20.o

$(BUILD_DIR)/mt19937.o: $(SRC_PROVIDERS_DIR)/mt19937.cpp $(INC_PROVIDERS_DIR)/mt19937.hpp
	$(CPP) $(CXXFLAGS) $(DEBUG) $(INCLUDE) -c $(SRC_PROVIDERS_DIR)/mt19937.cpp -o $(BUILD_DIR)/mt19937.o

$(BUILD_DIR)/util.o: $(SRC_DIR)/util.cpp $(INC_DIR)/util.hpp
	$(CPP) $(CXXFLAGS) $(DEBUG) $(INCLUDE) -c $(SRC_DIR)/util.cpp -o $(BUILD_DIR)/util.o

$(BUILD_DIR)/checksum.o: $(SRC_PROVIDERS_DIR)/checksum.cpp $(INC_PROVIDERS_DIR)/checksum.hpp
	$(CPP) $(CXXFLAGS) $(DEBUG) $(INCLUDE) -c $(SRC_PROVIDERS_DIR)/checksum.cpp -o $(BUILD_DIR)/checksum.o

