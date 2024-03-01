RM = rm -f
CC = g++
AR = ar
CP = cp -Rf
INSTALL = install -m 644
INCLUUDE = -I/usr/include -I/usr/local/include
LD_PATH = -L/usr/lib64 -L/usr/local/lib64
LIB_DIR = /usr/local/lib64
INCLUDE_DIR = /usr/local/include
LIB = /usr/local/lib64/libfileinterface.a
OPT = -O0 -Wall -std=c++17 -fPIC
TARGET = ConfFileReadSample
SRC = main.cpp

all:
	$(CC) $(INCLUDE) $(OPT) -o $(TARGET) $(SRC) $(LIB)

.PHONY: clean
clean:
	$(RM) *.o $(TARGET)

