RM = rm -f
CC = g++
AR = ar
CP = cp -Rf
INSTALL = install -o root -g root -m 644
INCLUUDE = -I/usr/include -I/usr/local/include
LD_PATH = -L/usr/lib64 -L/usr/local/lib64
LIB_DIR = /usr/local/lib64
INCLUDE_DIR = /usr/local/include
LIB = /usr/local/lib/libgtest.a /usr/local/lib/libgtest_main.a
OPT = -O0 -Wall -std=c++17
TARGET = domainTest
SRC = ../../src/domain/JsonCreator.cpp
OBJ = JsonCreator.o
TESTSRC = JsonCreatorTest.cpp
TESTOBJ = JsonCreatorTest.o

all: $(OBJ) $(TESTOBJ)
	$(CC) $(INCLUUDE) $(OPT) -o $(TARGET) $(OBJ) $(TESTOBJ) $(LIB)

$(OBJ):
	$(CC) $(INCLUUDE) $(OPT) -c $(SRC)

$(TESTOBJ):
	$(CC) $(INCLUUDE) $(OPT) -c $(TESTSRC)

.PHONY: clean install
clean:
	$(RM) *.o $(TARGET)

