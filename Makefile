CFLAGS=--std=c99 -O2 -Wall -Wextra -pedantic

annotate: annotate.o

clean:
	rm -f annotate *.o

.PHONY: clean
