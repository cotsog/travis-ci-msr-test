
all:  test-msr-access


test-msr-access: test-msr-access.c
	gcc -o $@  test-msr-access.c

.PHONY: clean test-msr-access

clean:
	rm -f test-msr-access


