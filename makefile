DEBUG = -g
CPP = g++
CXXFLAGS = -Wall -Wextra -O -std=c++17 -Iboost_1_81_0 -Wno-deprecated-declarations
CFLAGS = -Wall -Wextra -O -std=c11

airedale: vcppwd.o main.o
	$(CPP) $(DEBUG) $(CXXFLAGS) -o airedale vcppwd.o main.o

main.o: main.cpp getpass.h
	$(CPP) $(DEBUG) $(CXXFLAGS) -c main.cpp

vcppwd.o: vcppwd.cpp vcppwd.hpp
	$(CPP) $(DEBUG) $(CXXFLAGS) -c vcppwd.cpp

getpass.o: getpass.c
	$(CC) $(DEBUG) $(CFLAGS) -c getpass.c

clean:
	rm -f main.o getpass.o vcppwd.o main