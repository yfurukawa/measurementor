CC = g++
RM = rm -rf
MAKE = make
INCLUDE = -I/usr/include -I/usr/local/include
LIB_DIR = -L/usr/lib64 -L/usr/local/lib64 -L/usr/lib -L/usr/local/lib
LIB = pts/libpts.a /usr/local/lib64/libnetworkinterface.a
OPT = -O0 -Wall -std=c++17 -g
TARGET = measurementor
SRC = main.cpp
OBJ = main.o domain/PtsDataCollector.o

all: $(SRC:.cpp=.o)
	$(CC) $(INCLUDE) $(LIB_DIR) $(OPT) -o $(TARGET) $(OBJ) $(LIB)

$(SRC:.cpp=.o): $(SRC)
	$(CC) $(INCLUDE) $(LIB_DIR) $(OPT) -c $(SRC)

sub:
	cd domain ; $(MAKE) all
	cd pts ; $(MAKE) all

lib:
	cd pts ; $(MAKE) lib

.PHONY: clean
clean:
	$(RM) *.o $(TARGET)
	cd domain ; $(MAKE) clean
	cd pts ; $(MAKE) clean

