all:
	$(MAKE) -C files-fd-open
	$(MAKE) -C signals-caught
	$(MAKE) -C memory-shared-libs
	$(MAKE) -C timing

.PHONY: clean

clean:
	$(MAKE) -C files-fd-open		clean
	$(MAKE) -C signals-caught		clean
	$(MAKE) -C memory-shared-libs	clean
	$(MAKE) -C timing				clean
