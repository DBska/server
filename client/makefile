# inlude files directories:
INC=-I/usr/local/include/soci -I/usr/include/mysql

# Libraries and Libraries paths:
LIBS= -lmysqlclient -lpthread -lz -lm -ldl  -lsoci_core -lsoci_mysql
LIBS_PATH=-L/usr/lib/x86_64-linux-gnu -L/usr/local/lib64

# Compiler flags and compiler:
CFLAGS = -DBIG_JOINS=1  -fno-strict-aliasing   -g -DNDEBUG 
CC = g++

# Sources:
SOURCES = client.cpp
OBJS = $(SOURCES:.cpp=.o)

# Executable:
EXE = client

# makefile rules
all: $(SOURCES) $(EXE)

$(EXE): $(OBJS)
	$(CC) $< -o $@ $(LIBS_PATH) $(LIBS)

%.o: %.cc
	$(CC) $(INC)  $(CFLAGS) -c $< 

.PHONY: clean

clean:
	rm -f $(OBJS) $(EXE)


