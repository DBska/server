# inlude files directories:
INC=-I. -I/usr/local/include/soci -I/usr/include/mysql

# Libraries and Libraries paths:
LIBS= -lmysqlclient -lpthread -lz -lm -ldl  -lsoci_core -lsoci_mysql -lprotobuf -lpthread
LIBS_PATH=-L/usr/lib/x86_64-linux-gnu -L/usr/local/lib64

# Compiler flags and compiler:
CFLAGS = -DBIG_JOINS=1  -fno-strict-aliasing   -g #-DNDEBUG 
CC = g++

# Sources:
SOURCES = server.cpp oda.pb.cpp
OBJS = $(SOURCES:.cpp=.o)

# Executable:
EXE = server

# makefile rules
all: $(SOURCES) $(EXE)

$(EXE): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIBS_PATH) $(LIBS)

%.o: %.cpp
	$(CC) $(INC) $(CFLAGS) -c $< 

.PHONY: clean

clean:
	rm -f $(OBJS) $(EXE)


