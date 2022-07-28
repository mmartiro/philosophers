SRCS = $(shell find "." -name "*.c")
OBJS = ${SRCS:.c=.o}
NAME = philo
CC   = gcc
FLAGS = -Wall -Wextra -Werror

${NAME} : ${OBJS}
	${CC} ${FLAGS} ${SRCS} -o philo

all : ${NAME}

clean :
		rm -rf ${OBJS}

fclean : clean
		rm -rf ${NAME}

re : fclean all

.PHONY :
		all clean fclean