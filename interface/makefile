# inlude files directories:
INC=-I../proto/src

# Libraries and Libraries paths:
LIBS= -lprotobuf -lpthread -lproto
LIBS_PATH=-L../proto/src

# Compiler flags and compiler:
CFLAGS = -DBIG_JOINS=1  -fno-strict-aliasing   -g -DNDEBUG 
CC = g++

# Sources:
SOURCES = $(wildcard *.cpp)
OBJS = $(SOURCES:.cpp=.o)

# Library name:
LIBNAME=libinterface

# makefile rules
all: $(LIBNAME).a $(OBJS) 

$(LIBNAME).a: $(OBJS)
	ar rvs $(LIBNAME).a $(OBJS)
	cp $(LIBNAME).a ../tool/library/ 
	cp *.h ../tool/include/ 

%.o: %.cpp
	$(CC) $(INC)  $(CFLAGS) -c $< 

.PHONY: clean

clean:
	rm -f $(OBJS) $(LIBNAME).a 


