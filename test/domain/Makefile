RM = rm -f
CC = g++
MAKE = make
INCLUUDE = -I/usr/include -I/usr/local/include
LD_PATH = -L/usr/lib64 -L/usr/local/lib64
LIB = /usr/local/lib/libgtest.a /usr/local/lib/libgtest_main.a
OPT = -O0 -Wall -std=c++17
TARGET = domainTest
OBJ = ../../src/domain/JsonCreator.o ../../src/domain/Task.o ../../src/domain/Item.o ../../src/domain/Sprint.o ../../src/domain/Project.o
TESTSRC = JsonCreatorTest.cpp TaskTest.cpp ItemTest.cpp SprintTest.cpp ProjectTest.cpp
TESTOBJ = JsonCreatorTest.o TaskTest.o ItemTest.o SprintTest.o ProjectTest.o

all: $(OBJ) $(TESTOBJ)
	$(CC) $(INCLUUDE) $(OPT) -o $(TARGET) $(OBJ) $(TESTOBJ) $(LIB)

$(OBJ):
	$(MAKE) production

$(TESTOBJ):
	$(CC) $(INCLUUDE) $(OPT) -c $(TESTSRC)

production:
	cd ../../src/domain; $(MAKE)

.PHONY: clean install
clean:
	$(RM) *.o $(TARGET)
	cd ../../src/domain; $(MAKE) clean
