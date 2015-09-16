# inlude files directories:
INC=-I./include

# Libraries and Libraries paths:
LIBS= -linterface -lprotobuf -lpthread -lproto
LIBS_PATH=-L./library

# Compiler flags and compiler:
CFLAGS = -DBIG_JOINS=1  -fno-strict-aliasing   -g -DNDEBUG 
CC = g++

# Sources:
SOURCES = $(wildcard *.cpp)
OBJS = $(SOURCES:.cpp=.o)

# Executable:
EXE = tool

# makefile rules
all: $(SOURCES) $(EXE)

$(EXE): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIBS_PATH) $(LIBS)

%.o: %.cpp
	$(CC) $(INC)  $(CFLAGS) -c $< 

.PHONY: clean

clean:
	rm -f $(OBJS) $(EXE)


