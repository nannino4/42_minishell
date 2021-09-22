NAME		= minishell

SRCS		=	\
				exec/builtin.c \
				exec/cd.c \
				exec/echo.c \
				exec/env.c \
				exec/exec.c \
				exec/exit.c \
				exec/export.c \
				exec/pwd.c \
				exec/unset.c \
				exec/utils.c \
				parsing/final_parse.c \
				parsing/ioredir.c \
				parsing/pipes.c \
				parsing/quotes_and_variables.c \
				parsing/utils.c \
				parsing/utils2.c \
				utils/utils.c \
				utils/utils2.c \
				error.c \
				free.c \
				main.c

OBJS		= $(SRCS:.c=.o)

HOMEBREW	= ./homebrew/opt/readline/lib

CFLAGS		= -Wall -Wextra -Werror

%.o :		%.c
			gcc -c -g -I./include -I./libft -I ./homebrew/opt/readline/include $(CFLAGS) $< -o $@

all:		$(NAME)

$(NAME):	$(HOMEBREW) $(OBJS)
			make -C libft
			mv libft/libft.a .
			gcc $(OBJS) libft.a -o $(NAME) -lreadline -L ./homebrew/opt/readline/lib

$(HOMEBREW):
			mkdir homebrew && curl -L https://github.com/Homebrew/brew/tarball/master | tar xz --strip 1 -C homebrew
			./homebrew/bin/brew install readline

clean:
			rm -rf homebrew
			rm -f $(OBJS)
			make -C libft clean

fclean:		clean
			rm -f $(NAME) libft.a

re:			fclean all

.PHONY:		all clean fclean re
