CC = g++
RM = rm -rf
MAKE = make
INCLUDE = -I/usr/include -I/usr/local/include
LD_PATH = -L/usr/lib64 -L/usr/local/lib64 -L/usr/lib -L/usr/local/lib
LIB_DIR = /usr/local/lib64
LIB = -lnetworkinterface -lclock -lfileinterface
LIBD = -lnetworkinterfaced -lclockd -lfileinterfaced
DLIB= -llogger -lpqxx -lpq
OPT = -O0 -Wall -std=c++17 -fPIC -g
TARGET = measurementor
SRC = main.cpp
OBJ = main.o domain/PtsDataCollector.o domain/Project.o domain/Sprint.o domain/Item.o domain/Task.o domain/JsonCreator.o domain/MetricCalculator.o \
domain/ReworkCounter.o \
pts/customized_openproject/OpenProject.o pts/customized_openproject/OpenProjectFactory.o pts/customized_openproject/JsonParser.o pts/customized_openproject/PreviousDataReader.o \
pts/customized_openproject/PreviousDataReaderFactory.o pts/customized_openproject/DifferAbsorber.o \
analyzer/elasticsearch/Elasticsearch.o analyzer/elasticsearch/ElasticsearchFactory.o analyzer/elasticsearch/Index.o \
repository/postgresql/Repository.o repository/postgresql/RepositoryFactory.o repository/postgresql/ReworkRepository.o repository/postgresql/ReworkRepositoryFactory.o

export CC RM MAKE INCLUDE LD_PATH OPT

$(TARGET): $(OBJ)
	$(CC) $(INCLUDE) $(LD_PATH) $(OPT) -o $(TARGET) $(OBJ) $(LIBD) $(DLIB)

$(OBJ):
	$(CC) $(INCLUDE) $(LD_PATH) $(OPT) -c $(SRC)
	cd domain ; $(MAKE)
	cd pts/customized_openproject ; $(MAKE)
	cd analyzer/elasticsearch ; $(MAKE)
	cd repository/postgresql; $(MAKE)

.PHONY: clean
clean:
	$(RM) *.o $(TARGET)
	cd domain ; $(MAKE) clean
	cd pts/customized_openproject ; $(MAKE) clean
	cd analyzer/elasticsearch ; $(MAKE) clean
	cd repository/postgresql; $(MAKE) clean
