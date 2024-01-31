RM = rm -f
CC = g++
CP = cp -a
INCLUUDE = -I/usr/include -I/usr/local/include
LD_PATH = -L/usr/lib64 -L/usr/local/lib64
LIB_DIR = /usr/local/lib64
LIB = /usr/local/lib64/libnetworkinterface.a
OPT = -O0 -Wall -std=c++17
TARGET = TcpClient
SRC = main.cpp

$(TARGET): $(SRC:.cpp=.o)
	$(CC) $(INCLUUDE) $(LD_PATH) $(OPT) -o $(TARGET) $(SRC:.cpp=.o) $(LIB)

$(SRC:.cpp=.o): $(SRC)
	$(CC) $(INCLUUDE) $(LD_PATH) $(OPT) -c $(SRC)

.PHONY: clean install
clean:
	$(RM) *.o $(TARGET)

install:
	$(CP) $(TARGET) $(LIB_DIR)
