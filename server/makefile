# inlude files directories:
INC=-I/usr/local/include/soci -I/usr/include/mysql -I../proto/src

# Libraries and Libraries paths:
LIBS= -lmysqlclient -lpthread -lz -lm -ldl  -lsoci_core -lsoci_mysql -lprotobuf -lpthread -lproto
LIBS_PATH=-L/usr/lib/x86_64-linux-gnu -L/usr/local/lib64 -L../proto/src

# Compiler flags and compiler:
CFLAGS = -DBIG_JOINS=1  -fno-strict-aliasing   -g -DNDEBUG 
CC = g++

# Sources:
SOURCES = $(wildcard *.cpp)
OBJS = $(SOURCES:.cpp=.o)

# Executable:
EXE = server

# makefile rules
all: $(SOURCES) $(EXE)

$(EXE): $(OBJS)
	$(CC) $(OBJS) $(LIBS_PATH) $(LIBS) -o $@ 

%.o: %.cpp
	$(CC) $(INC) $(CFLAGS) -c $< 

.PHONY: clean

clean:
	rm -f $(OBJS) $(EXE)


