RM = rm -f
CC = g++
MAKE = make
INCLUUDE = -I/usr/include -I/usr/local/include
LD_PATH = -L/usr/lib64 -L/usr/local/lib64
LIB_DIR = /usr/local/lib64
INCLUDE_DIR = /usr/local/include
LIB = /usr/local/lib/libgtest.a /usr/local/lib/libgtest_main.a
OPT = -O0 -Wall -std=c++17
TARGET = test
OBJ = ../Chronos.o ../ISO8601String.o ../TimeProvider.o
TESTSRC = ChronosTest.cpp ISO8601StringTest.cpp
TESTOBJ = ChronosTest.o ISO8601StringTest.o

all: $(OBJ) $(TESTOBJ)
	$(CC) $(INCLUUDE) $(OPT) -o $(TARGET) $(OBJ) $(TESTOBJ) $(LIB)

$(OBJ):
	$(MAKE) production

$(TESTOBJ):
	$(CC) $(INCLUUDE) $(OPT) -c $(TESTSRC)

production:
	cd ../; $(MAKE)

.PHONY: clean install
clean:
	$(RM) *.o $(TARGET)
	cd ../; $(MAKE) clean
	