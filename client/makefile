# inlude files directories:
INC=-I.

# Libraries and Libraries paths:
LIBS= -lprotobuf -lpthread
LIBS_PATH=

# Compiler flags and compiler:
CFLAGS = -DBIG_JOINS=1  -fno-strict-aliasing   -g # -DNDEBUG 
CC = g++

# Sources:
SOURCES = client.cpp oda.pb.cpp
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


