RM = rm -rf
CC = g++
AR = ar
CP = cp -Rf
LN = ln -s
INSTALL = install -o root -g root -m 644
MKDIR = mkdir -p -m 644
MAKE = make
INCLUUDE = -I/usr/include -I/usr/local/include
LD_PATH = -L/usr/lib64 -L/usr/local/lib64
LIB_DIR = /usr/local/lib64
INCLUDE_DIR = /usr/local/include
LIB = 
OPT = -O0 -Wall -std=c++17 -fPIC
TARGET = libnetworkinterface.a.0.6.0
TARGETD = libnetworkinterfaced.a.0.6.0
SRC = UdpClient.cpp Port.cpp IPv4.cpp Hostname.cpp TcpClient.cpp NetworkIfHelper.cpp RestAPIHelper.cpp TcpClientMock.cpp

$(TARGET):
	$(CC) $(INCLUUDE) $(OPT) -c $(SRC)
	$(AR) rc -o $(TARGET) $(SRC:.cpp=.o)
	$(MAKE) debug

debug:
	$(CC) $(INCLUUDE) $(OPT) -g -c $(SRC)
	$(AR) rc -o $(TARGETD) $(SRC:.cpp=.o)

.PHONY: clean install
clean:
	$(RM) *.o $(TARGET) $(TARGETD)

install:
	$(MKDIR) $(LIB_DIR)
	$(MKDIR) $(INCLUDE_DIR)/skills
	$(INSTALL) $(TARGET) $(LIB_DIR)
	$(INSTALL) $(TARGETD) $(LIB_DIR)
	$(INSTALL) *.h $(INCLUDE_DIR)
	$(INSTALL) skills/* $(INCLUDE_DIR)/skills
	$(RM) $(LIB_DIR)/libnetworkinterface.a
	$(RM) $(LIB_DIR)/libnetworkinterfaced.a
	$(LN) $(LIB_DIR)/$(TARGET) $(LIB_DIR)/libnetworkinterface.a
	$(LN) $(LIB_DIR)/$(TARGETD) $(LIB_DIR)/libnetworkinterfaced.a