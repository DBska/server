
all: proto
	$(MAKE) -C src

proto:  
ifeq ($(wildcard src/*.cc),)
	protoc --cpp_out=./src *.proto
endif

.PHONY: clean 

clean:
	$(MAKE) -C src clean

