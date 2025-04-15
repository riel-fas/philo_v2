
NAME		=	philo

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror


SRCS		=	philo_main.c \
				philo_parsing.c \
				philo_routine.c \
				philo_thread.c \
				philo_utils.c \
				philo_forks_init.c \
				philo_init.c \
				philo_monitor.c



OBJS		=	${SRCS:.c=.o}

HEADER		=	philosophers.h

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c	$(HEADER)
			$(CC) $(CFLAGS) -c $< -o $@

clean	:
			rm -rf $(OBJS)

fclean	:	clean
			rm -rf $(NAME)

re		:	fclean all

.phony	:	all clean fclean re



