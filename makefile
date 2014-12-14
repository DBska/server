all:
	$(MAKE) -C server
	$(MAKE) -C client

proto:
	protoc oda.proto --cpp_out=client

.PHONY: clean

clean:
	$(MAKE) -C server clean
	$(MAKE) -C client clean


