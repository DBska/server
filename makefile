all:
	$(MAKE) -C proto
	$(MAKE) -C server
	$(MAKE) -C client
	$(MAKE) -C interface
	$(MAKE) -C tool
	$(MAKE) -C java

proto:
	$(MAKE) -C proto


.PHONY: clean help proto

help:
	@echo "Usage:"
	@echo "make all builds proto classes, server, client, tool and interface"
	@echo "make proto builds only pb classes"
	@echo "make clean clean both client and server"


clean:
	$(MAKE) -C server clean
	$(MAKE) -C client clean
	$(MAKE) -C proto clean
	$(MAKE) -C interface clean
	$(MAKE) -C tool clean
	$(MAKE) -C java clean


