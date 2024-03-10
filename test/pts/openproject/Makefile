RM = rm -f
CC = g++
MAKE = make
INCLUUDE = -I/usr/include -I/usr/local/include
LD_PATH = -L/usr/lib64 -L/usr/local/lib64
LIB_DIR = /usr/local/lib64
INCLUDE_DIR = /usr/local/include
LIB = /usr/local/lib/libgtest.a /usr/local/lib/libgtest_main.a /usr/local/lib64/libnetworkinterface.a /usr/local/lib64/libclock.a /usr/local/lib64/libfileinterface.a
OPT = -O0 -Wall -std=c++17
TARGET = openprojectTest
OBJ = ../../../src/pts/openproject/JsonParser.o ../../../src/pts/openproject/OpenProject.o
TESTSRC = JsonParserTest.cpp OpenProjectTest.cpp
TESTOBJ = JsonParserTest.o OpenProjectTest.o

all: $(OBJ) $(TESTOBJ)
	$(CC) $(INCLUUDE) $(OPT) -o $(TARGET) $(OBJ) $(TESTOBJ) $(LIB)

$(OBJ):
	$(MAKE) production

$(TESTOBJ):
	$(CC) $(INCLUUDE) $(OPT) -c $(TESTSRC)

production:
	cd ../../../src/pts/openproject; $(MAKE)

.PHONY: clean install
clean:
	$(RM) *.o $(TARGET)
	cd ../../../src/pts/openproject; $(MAKE) clean
