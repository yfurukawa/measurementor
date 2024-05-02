CC = g++
RM = rm -rf
MAKE = make
INCLUDE = -I/usr/include -I/usr/local/include
LD_PATH = -L/usr/lib64 -L/usr/local/lib64 -L/usr/lib -L/usr/local/lib
LIB = -lnetworkinterface -lclock -lfileinterface -llogger -lpqxx -lpq
LIBD = -lnetworkinterfaced -lclockd -lfileinterfaced -llogger -lpqxx -lpq
OPT = -O0 -Wall -std=c++17 -fPIC -g
TARGET = measurementor
SRC = main.cpp
OBJ = main.o domain/PtsDataCollector.o domain/Project.o domain/Sprint.o domain/Item.o domain/Task.o domain/JsonCreator.o domain/MetricCalculator.o \
domain/ReworkCounter.o \
pts/openproject/OpenProject.o pts/openproject/OpenProjectFactory.o pts/openproject/JsonParser.o pts/openproject/PreviousDataReader.o \
pts/openproject/PreviousDataReaderFactory.o pts/openproject/DifferAbsorber.o\
analyzer/elasticsearch/Elasticsearch.o analyzer/elasticsearch/ElasticsearchFactory.o analyzer/elasticsearch/Index.o \
repository/postgresql/Repository.o repository/postgresql/RepositoryFactory.o repository/postgresql/ReworkRepository.o \
repository/postgresql/ReworkRepositoryFactory.o

export CC RM MAKE INCLUDE LD_PATH OPT

all: $(OBJ)
	$(CC) $(INCLUDE) $(LD_PATH) $(OPT) -o $(TARGET) $(OBJ) $(LIBD)

$(SRC:.cpp=.o): $(SRC)
	$(CC) $(INCLUDE) $(LD_PATH) $(OPT) -c $(SRC)
	$(MAKE) sub

sub:
	cd domain ; $(MAKE) all
	cd pts/openproject ; $(MAKE) all
	cd analyzer/elasticsearch ; $(MAKE) all
	cd repository/postgresql; $(MAKE) all

.PHONY: clean
clean:
	$(RM) *.o $(TARGET)
	cd domain ; $(MAKE) clean
	cd pts/openproject ; $(MAKE) clean
	cd analyzer/elasticsearch ; $(MAKE) clean
	cd repository/postgresql; $(MAKE) clean
