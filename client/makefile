# inlude files directories:
INC=-I../proto/src

# Libraries and Libraries paths:
LIBS= -lprotobuf -lpthread -lproto
LIBS_PATH=-L../proto/src -L/usr/lib -L/usr/local/lib


# Compiler flags and compiler:
CFLAGS = -DBIG_JOINS=1  -fno-strict-aliasing   -g -DNDEBUG 
CC = g++

# Sources:
SOURCES = $(wildcard *.cpp)
OBJS = $(SOURCES:.cpp=.o)

# Executable:
EXE = client

# makefile rules
all: $(SOURCES) $(EXE)

$(EXE): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIBS_PATH) $(LIBS)

%.o: %.cpp
	$(CC) $(INC)  $(CFLAGS) -c $< 

.PHONY: clean

clean:
	rm -f $(OBJS) $(EXE)


