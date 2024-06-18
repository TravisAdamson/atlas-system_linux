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
	${CC} ${CFLAGS} 0-hreadelf.c osabi.c machine.c type.c offset.c headers.c readelf.h -o 0-hreadelf