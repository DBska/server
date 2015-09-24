# Compiler flags and compiler:
CFLAGS = -DBIG_JOINS=1  -fno-strict-aliasing   -g -DNDEBUG 
CC = g++

# Sources:
SOURCES = $(wildcard *.cc)
OBJS = $(SOURCES:.cc=.o)

# Library name:
LIBNAME=libproto

all: $(OBJS) $(LIBNAME).a

$(LIBNAME).a: $(OBJS)
	ar rvs $(LIBNAME).a $(OBJS)
	cp $(LIBNAME).a ../../tool/library
	cp *.h ../../tool/include

# makefile rules
%.o: %.cc
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(OBJS) $(LIBNAME).a *.cc *.h


