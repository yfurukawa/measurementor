CC = g++
RM = rm -rf
AR = ar rc
MV = mv
INCLUDE = -I/usr/include -I/usr/local/include
LIB_DIR = -L/usr/lib64 -L/usr/local/lib64 -L/usr/lib -L/usr/local/lib
OPT = -O0 -Wall -std=c++17 -fPIC -g
TARGET = libpts.a
SRC = OpenProject.cpp OpenProjectFactory.cpp JsonParser.cpp ../../../lib/libclock/Chronos.cpp ../../../lib/libfileinterface/src/ConfFileParser.cpp ../../../lib/libfileinterface/src/TextFileReader.cpp

all:
	$(CC) $(INCLUDE) $(LIB_DIR) $(OPT) -c $(SRC)
	$(AR) -o $(TARGET) $(SRC:.cpp=.o)
	$(MV) $(TARGET) ..

.PHONY: clean
clean:
	$(RM) *.o ../$(TARGET)

