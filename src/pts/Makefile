CC = g++
RM = rm -rf
AR = ar rc
INCLUDE = -I/usr/include -I/usr/local/include
LIB_DIR = -L/usr/lib64 -L/usr/local/lib64 -L/usr/lib -L/usr/local/lib
LIB = /usr/local/lib64/libnetworkinterface.a
OPT = -O0 -Wall -std=c++17 -fPIC
TARGET = libpts.a
SRC = OpenProject.cpp OpenProjectFactory.cpp

lib:
	$(CC) $(INCLUDE) $(LIB_DIR) $(OPT) -c $(SRC)
	$(AR) -o $(TARGET) $(SRC:.cpp=.o)

.PHONY: clean
clean:
	$(RM) *.o $(TARGET)

