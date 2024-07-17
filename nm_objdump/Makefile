CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89 -g

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

HOBJ_SRC = $(wildcard hobj*.c)
HNM_SRC = $(filter-out $(HOBJ_SRC), $(SRC))

HOBJ_OBJ = $(HOBJ_SRC:.c=.o)
HNM_OBJ = $(HNM_SRC:.c=.o)

all: hnm hobj

hnm: $(HNM_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

hobjdump: $(HOBJ_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o hnm hobjdump
