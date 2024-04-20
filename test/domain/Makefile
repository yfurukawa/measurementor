CC = g++
RM = rm -f
MAKE = make
INCLUDE = -I/usr/include -I/usr/local/include 
LD_PATH = -L/usr/lib64 -L/usr/local/lib64 -L/usr/lib -L/usr/local/lib
LIB = -lgtest lgtest_main -lclock　-llogger -lpqxx -lpq
OPT = -O0 -Wall -std=c++17
TARGET = domainTest
OBJ = ../../src/domain/JsonCreator.o ../../src/domain/Task.o ../../src/domain/Item.o ../../src/domain/Sprint.o ../../src/domain/Project.o ../../src/domain/MetricCalculator.o
TESTSRC = JsonCreatorTest.cpp TaskTest.cpp ItemTest.cpp SprintTest.cpp ProjectTest.cpp MetricCalculatorTest.cpp MetricCalculatorSpy.cpp \
RepositoryMock.cpp RepositoryMockFactory.cpp AnalyzerMock.cpp AnalyzerMockFactory.cpp
TESTOBJ = JsonCreatorTest.o TaskTest.o ItemTest.o SprintTest.o ProjectTest.o MetricCalculatorTest.o MetricCalculatorSpy.o \
RepositoryMock.o RepositoryMockFactory.o AnalyzerMock.o AnalyzerMockFactory.o

export CC RM MAKE INCLUDE LD_PATH OPT

all: $(OBJ) $(TESTOBJ)
	$(CC) $(INCLUDE) $(OPT) -o $(TARGET) $(OBJ) $(TESTOBJ) $(LIB)

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
