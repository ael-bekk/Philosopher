NAME	= philo_bonus

LIB	= libfilo.a

SRCS	= srcs/creat_threads.c srcs/ft_atoi.c  srcs/ft_itoa.c  srcs/routine.c srcs/watch_threads.c srcs/main_bonus.c

OBJS	= $(SRCS:.c=.o)

ICLS	= libft.h

CFLAGS	= -Wall -Wextra -Werror

CC		= cc

RM		= rm -f

all:		$(NAME)

$(NAME):	$(LIB)
	$(CC) $(CFLAGS) $(LIB) -o $(NAME)

$(LIB):	$(OBJS)
	ar -rcs $(LIB) $(OBJS)

clean:
	$(RM) $(OBJS) $(LIB)

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re
