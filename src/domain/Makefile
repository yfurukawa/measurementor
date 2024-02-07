CC = g++
RM = rm -rf
MAKE = make
INCLUDE = -I/usr/include -I/usr/local/include
LIB_DIR = -L/usr/lib64 -L/usr/local/lib64 -L/usr/lib -L/usr/local/lib
LIB = ../pts/libpts.a
OPT = -O0 -Wall -std=c++17 -g
SRC = PtsDataCollector.cpp Project.cpp Item.cpp Task.cpp Sprint.cpp

all:
	$(CC) $(INCLUDE) $(LIB_DIR) $(OPT) -c $(SRC)

.PHONY: clean
clean:
	$(RM) *.o $(TARGET)

