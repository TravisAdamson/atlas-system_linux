CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89 -g

SRC = $(wildcard *.c)
nm = $(patsubst %.c, %.o, $(wildcard nm*.c))
objdump = $(patsubst %.c, %.o, $(wildcard objdump*.c))

.PHONY: hnm hobjdump clean

hnm: $(SRC)
	$(CC) $(CFLAGS) $(0) -o hnm $^

hobjdump:
	@echo '#!/bin/bash' > $@
	@echo '( exec -a "./hobjdump" objdump -sf $$1 )' >> $@
	chmod u+x -v $@

clean:
	rm -f hnm
	rm -f *.o
