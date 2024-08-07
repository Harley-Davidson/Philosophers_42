SRC	= 		main.c			\
			philosopher.c	\
			table.c			\
			utils.c

SRC_bonus	=	main.c			\
				philosopher.c	\
				table.c			\
				utils.c

OBJS	= $(SRC:.c=.o)

OBJS_bonus	= $(SRC_bonus:.c=.o)

NAME	= philo.a

NAME_bonus	= philo_bonus.a

AR	= ar rcs

RM	= rm -f

LIB	= ranlib

GCC	= gcc

CFLAGS	= -Wall -Wextra -Werror

all:	$(NAME)

$(NAME):	$(OBJS)
		$(AR) $(NAME) $(OBJS)
		$(LIB) $(NAME)

bonus:	$(OBJS_bonus)
	$(AR) $(NAME_bonus) $(OBJS_bonus)
	$(LIB) $(NAME_bonus)

.c.o:
	$(GCC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
	rm -f $(OBJS) $(OBJS_bonus)
	
fclean:	clean
	rm -f $(NAME) $(NAME_bonus)
	
re:	fclean all

.PHONY:	all bonus clean fclean re
