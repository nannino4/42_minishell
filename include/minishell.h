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

typedef struct  s_list
{
    struct s_list *previous;
    struct s_list *next;
    char *line;
    char **split;
    int fd_out;
    int fd_in;
}               t_list;

typedef struct  s_data
{
    t_list *list;
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

int ft_parse_pipes(t_data *data);
int	ft_parse_ioredir(t_data *data);
int ft_final_parse(t_data *data);

void ft_add_elem(t_data *data, t_list *elem);
char *ft_get_name(char **line, int *i, char **env, int flag);
void ft_readline(char *end_word, int *fd);
int ft_skip_quotes(char *line, int i);

int	ft_parse_single_quotes(char **line, int i);
int	ft_parse_double_quotes(char **line, int i, char **env, int flag);
int	ft_parse_variables(char **line, int i, char **env);

int ft_cut_line_io_redir(char **line, int i, int j);

/* error */

void ft_free_list(t_list *list);

#endif