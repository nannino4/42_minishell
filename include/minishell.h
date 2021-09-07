#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

/* commands */

void	ft_check_echo(char **stringa);

/* utils */

int	ft_istoken(char c);
char	*ft_get_name(char *line, int *i);
int	ft_skip_spaces(char *line, int i);

/* parsing */

void	ft_parse_and_execute(char *line);
void	ft_parse(char **line);

int	ft_check_for_single_quotes(char **line, int i);
int	ft_check_for_double_quotes(char **line, int i);

int    ft_check_for_redir(char **line, int i);
void	ft_input_redir(char **line, int i);

void	ft_cut_line_io_redir(char **line, int i, int j);
int	ft_cut_line_quotes(char **line, int i, int j);

#endif