# inlude files directories:
INC=-I./include

# Libraries and Libraries paths:
LIBS= -linterface -lprotobuf -lpthread -lproto
LIBS_PATH=-L./library -L/usr/local/lib -L/usr/lib

# Compiler flags and compiler:
CFLAGS = -DBIG_JOINS=1  -fno-strict-aliasing   -g -DNDEBUG 
CC = g++

# Sources:
SOURCES = $(wildcard *.cpp)
OBJS = $(SOURCES:.cpp=.o)

# Executable:
EXE = tool

# makefile rules
all: lib $(SOURCES) $(EXE)

lib:
	cp ../interface/libinterface.a library/
	cp ../proto/src/libproto.a library/


$(EXE): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIBS_PATH) $(LIBS)

%.o: %.cpp
	$(CC) $(INC)  $(CFLAGS) -c $< 

.PHONY: clean lib

clean:
	rm -f $(OBJS) $(EXE)
	rm -f library/*.a


