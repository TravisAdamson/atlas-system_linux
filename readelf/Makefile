CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -g
SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=%.o)
NAME = hsh
RM = rm

all: ${OBJ}
	${CC} ${CFLAGS} ${SRC} -o ${NAME}

clean:
	${RM} -f *.o ${NAME}

oclean:
	${RM} -f ${OBJ}

fclean: clean oclean

re: oclean all

0-hreadelf: 0-hreadelf.c
	${CC} ${CFLAGS} 0-hreadelf.c osabi.c machine.c type.c offset.c headers.c v32conv.c readelf.h -o 0-hreadelf

1-hreadelf: 1-hreadelf.c
	${CC} ${CFLAGS} 1-hreadelf.c 1hreadelf.h helper.c helper2.c helper3.c helper4.c -o 1-hreadelf

2-hreadelf: 2-hreadelf.c
	${CC} ${CFLAGS} 2-hreadelf.c 2-getters.c 2-converts.c 2-printers.c 2hreadelf.h -o 2-hreadelf
