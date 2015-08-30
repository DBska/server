all:
	$(MAKE) -C proto
	$(MAKE) -C server
	$(MAKE) -C client

proto:
	$(MAKE) -C proto


.PHONY: clean help proto

help:
	@echo "Usage:"
	@echo "make all builds proto classes, server and client"
	@echo "make proto builds only pb classes"
	@echo "make clean clean both client and server"


clean:
	$(MAKE) -C server clean
	$(MAKE) -C client clean
	$(MAKE) -C proto clean


