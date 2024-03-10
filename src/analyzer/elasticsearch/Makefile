CC = g++
RM = rm -rf
INCLUDE = -I/usr/include -I/usr/local/include
LIB_DIR = -L/usr/lib64 -L/usr/local/lib64 -L/usr/lib -L/usr/local/lib
OPT = -O0 -Wall -std=c++17 -fPIC -g
SRC = Elasticsearch.cpp ElasticsearchFactory.cpp Index.cpp

all:
	$(CC) $(INCLUDE) $(LIB_DIR) $(OPT) -c $(SRC)

.PHONY: clean
clean:
	$(RM) *.o
