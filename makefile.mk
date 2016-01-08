all: $(binaries)

%: %.c
	$(CC) -o $@ $<

.PHONY: clean

clean:
	@rm -f $(binaries)
