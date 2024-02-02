CC = g++
RM = rm -rf
MAKE = make
INCLUDE = -I/usr/include -I/usr/local/include
LIB_DIR = -L/usr/lib64 -L/usr/local/lib64 -L/usr/lib -L/usr/local/lib
LIB = pts/libpts.a /usr/local/lib64/libnetworkinterface.a
OPT = -O0 -Wall -std=c++17
TARGET = measurementor
SRC = main.cpp

all: $(SRC:.cpp=.o)
	$(CC) $(INCLUDE) $(LIB_DIR) $(OPT) -o $(TARGET) $(SRC:.cpp=.o) $(LIB)

$(SRC:.cpp=.o): $(SRC)
	$(CC) $(INCLUDE) $(LIB_DIR) $(OPT) -c $(SRC)

lib:
	cd pts ; $(MAKE) lib

.PHONY: clean
clean:
	$(RM) *.o $(TARGET)
	cd pts ; $(MAKE) clean

