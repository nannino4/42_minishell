NAME		= minishell

SRCS		=	\
				parsing/cut_line.c \
				parsing/io_redir.c \
				parsing/parse.c \
				parsing/quotes.c \
				parsing/variables.c \
				utils/utils.c \
				utils/utils2.c \
				main.c

OBJS		= $(SRCS:.c=.o)

CFLAGS		= -Wall -Wextra -Werror

%.o :		%.c
			gcc -c -g -I./include -I./libft $(CFLAGS) $< -o $@

$(NAME):	$(OBJS)
			make -C libft
			mv libft/libft.a .
			gcc $(OBJS) libft.a -o $(NAME) -lreadline

all:		$(NAME)

clean:
			rm -f $(OBJS)
			make -C libft clean

fclean:		clean
			rm -f $(NAME) libft.a

re:			fclean all

.PHONY:		all clean fclean re
