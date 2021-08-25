#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

/* command.c */

int	ft_check_echo(char **stringa);
int	ft_check_for_single_quotes(char **line, int i);
int	ft_check_for_double_quotes(char **line, int i);

#endif