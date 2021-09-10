#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

# define WITH_VARIABLES 1
# define NO_VARIABLES 0

typedef struct  s_commands
{
    struct s_commands *previous;
    struct s_commands *next;
    char *line;
    char **split;
    int fd_out;
    int fd_in;
}               t_commands;

typedef struct  s_data
{
    t_commands list;
    char *line;
    char **env;
    char **local_env;
}               t_data;

/* utils */

int	ft_istoken(char c);
int	ft_isspace(char c);
int ft_isquotes(char c);

int	ft_skip_spaces(char *line, int i);
char **ft_env_creation(char **envp);
char *ft_getenv(char *var, char **env);

/* parsing */

void	ft_parse_and_execute(t_data *data);
void	ft_parse(t_data *data);
char    *ft_get_name(char **line, int *i, char **env, int flag);

int	ft_check_for_single_quotes(char **line, int i);
int	ft_check_for_double_quotes(char **line, int i, char **env, int flag);

int	ft_check_for_variables(char **line, int i, char **env);

int    ft_check_for_redir(char **line, int i, char **env);
void	ft_input_redir(char **line, int i, char **env);

void	ft_cut_line_io_redir(char **line, int i, int j);
int	ft_cut_line_quotes(char **line, int i, int j);

#endif