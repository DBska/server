
all: proto
	$(MAKE) -C src

proto:  
ifeq ($(wildcard src/*.cc),)
	protoc --cpp_out=./src *.proto
endif
ifeq ($(wildcard PHT/*.java),)
	protoc --java_out=. *.proto
	rm -f ../java/PHT/*.java
	cp ./PHT/*.java ../java/PHT
endif


.PHONY: clean 

clean:
	$(MAKE) -C src clean
	rm -f PHT/*.java

