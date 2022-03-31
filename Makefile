SRCS		= main.c		\
			  func_ft.c		\
			  initialize.c	\
			  parse.c		\
			  routine.c

OBJS		= ${SRCS:.c=.o} 

NAME		= Philosophers


CC			= clang

CCFLAGS	= -g3 -Wall -Werror -Wextra -pthread

%.o: %.c 
		$(CC) $(CCFLAGS) -c $< -o $@

all:		${NAME}

bonus:		${NAME}

${NAME}:	$(OBJS)
			$(CC) $(CCFLAGS) $(OBJS) -o $(NAME)

clean:
					rm -f ${OBJS}

fclean:		clean
					rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
