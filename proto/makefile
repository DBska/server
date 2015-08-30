# Compiler flags and compiler:
CFLAGS = -DBIG_JOINS=1  -fno-strict-aliasing   -g -DNDEBUG 
CC = g++

# Sources:
SOURCES = $(wildcard *.cc)
OBJS = $(SOURCES:.cc=.o)

all: $(OBJS) proto.a

libproto.a: $(OBJS)
	ar rvs libproto.a $(OBJS)

# makefile rules
%.o: %.cc
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f *.o libproto.a


