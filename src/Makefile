CC = g++
RM = rm -rf
MAKE = make
INCLUDE = -I/usr/include -I/usr/local/include
LIB_DIR = -L/usr/lib64 -L/usr/local/lib64 -L/usr/lib -L/usr/local/lib
LIB = /usr/local/lib64/libnetworkinterface.a /usr/local/lib64/libclock.a /usr/local/lib64/libfileinterface.a
OPT = -O0 -Wall -std=c++17 -g
TARGET = measurementor
SRC = main.cpp
OBJ = main.o domain/PtsDataCollector.o domain/Project.o domain/Sprint.o domain/Item.o domain/Task.o domain/JsonCreator.o \
pts/openproject/OpenProject.o pts/openproject/OpenProjectFactory.o pts/openproject/JsonParser.o \
analyzer/elasticsearch/Elasticsearch.o analyzer/elasticsearch/ElasticsearchFactory.o analyzer/elasticsearch/Index.o

all: $(SRC:.cpp=.o)
	$(CC) $(INCLUDE) $(LIB_DIR) $(OPT) -o $(TARGET) $(OBJ) $(LIB)

$(SRC:.cpp=.o): $(SRC)
	$(CC) $(INCLUDE) $(LIB_DIR) $(OPT) -c $(SRC)
	$(MAKE) sub

sub:
	cd domain ; $(MAKE) all
	cd pts/openproject ; $(MAKE) all
	cd analyzer/elasticsearch ; $(MAKE) all

.PHONY: clean
clean:
	$(RM) *.o $(TARGET)
	cd domain ; $(MAKE) clean
	cd pts/openproject ; $(MAKE) clean
	cd analyzer/elasticsearch ; $(MAKE) clean

