RM = rm -f
CC = g++
MAKE = make
INCLUUDE = -I/usr/include -I/usr/local/include
LD_PATH = -L/usr/lib64 -L/usr/local/lib64
LIB = /usr/local/lib/libgtest.a /usr/local/lib/libgtest_main.a /usr/local/lib64/libnetworkinterface.a
OPT = -O0 -Wall -std=c++17
TARGET = analyzerTest
OBJ = ../../../src/analyzer/elasticsearch/Index.o ../../../src/analyzer/elasticsearch/Elasticsearch.o
TESTSRC = IndexTest.cpp ElasticsearchTest.cpp
TESTOBJ = IndexTest.o ElasticsearchTest.o

all: $(OBJ) $(TESTOBJ)
	$(CC) $(INCLUUDE) $(OPT) -o $(TARGET) $(OBJ) $(TESTOBJ) $(LIB)

$(OBJ):
	$(MAKE) production

$(TESTOBJ):
	$(CC) $(INCLUUDE) $(OPT) -c $(TESTSRC)

production:
	cd ../../../src/analyzer/elasticsearch; $(MAKE)

.PHONY: clean
clean:
	$(RM) *.o $(TARGET)
	cd ../../../src/analyzer/elasticsearch; $(MAKE) clean
