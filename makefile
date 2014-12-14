all:
	$(MAKE) -C server
	$(MAKE) -C client

clientproto:
	protoc oda.proto --cpp_out=client

serverproto:
	protoc oda.proto --cpp_out=server

allproto: clientproto serverproto

.PHONY: clean help

help:
	@echo "Usage:"
	@echo "make allproto"
	@echo "make clientproto"
	@echo "make serverproto"


clean:
	$(MAKE) -C server clean
	$(MAKE) -C client clean


