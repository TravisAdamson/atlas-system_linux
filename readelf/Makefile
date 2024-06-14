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
