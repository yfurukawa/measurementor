RM = rm -f
CC = g++
AR = ar
CP = cp -Rf
INSTALL = install -m 644
INCLUUDE = -I/usr/include -I/usr/local/include
LD_PATH = -L/usr/lib64 -L/usr/local/lib64
LIB_DIR = /usr/local/lib64
INCLUDE_DIR = /usr/local/include
LIB = 
OPT = -O0 -Wall -std=c++17 -fPIC
TARGET = libclock.a.0.2.0
SRC = Chronos.cpp ChronosMock.cpp

$(TARGET):
	$(CC) $(INCLUUDE) $(OPT) -c $(SRC)
	$(AR) rc -o $(TARGET) $(SRC:.cpp=.o)

.PHONY: clean install
clean:
	$(RM) *.o $(TARGET)

install:
	$(INSTALL) $(TARGET) $(LIB_DIR)
	$(INSTALL) *.h $(INCLUDE_DIR)
