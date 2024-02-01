CC = g++
RM = rm -rf
INCLUDE = -I/usr/include -I/usr/local/include
LIB_DIR = -L/usr/lib64 -L/usr/local/lib64 -L/usr/lib -L/usr/local/lib
OPT = -O0 -Wall -std=c++17
TARGET = measurementor
SRC = main.cpp pts/OpenProject.cpp

all: $(SRC:.cpp=.o)
	$(CC) $(INCLUDE) $(LIB_DIR) $(OPT) -o $(TARGET) $(SRC:.cpp=.o)

$(SRC:.cpp=.o): $(SRC)
	$(CC) $(INCLUDE) $(LIB_DIR) $(OPT) -c $(SRC)

.PHONY: clean
clean:
	$(RM) *.o $(TARGET)

