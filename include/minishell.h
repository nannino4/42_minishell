#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "color.h"

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
    char *status_var;
}               t_data;

/* utils */

int	ft_istoken(char c);
int	ft_isspace(char c);
int ft_isquotes(char c);

int	ft_skip_spaces(char *line, int i);
char **ft_env_creation(char **envp);
char *ft_getenv(char *var, char **env);

/* exec */

void ft_exec(t_data *data);
void ft_set_io(t_list *list);
char *ft_join_path_and_cmd(char *path, char *command);

int ft_check_builtin(char *command);
void ft_exec_builtin(char *command, t_data *data);

/* parsing */

int ft_parse_pipes(t_data *data);
int	ft_parse_ioredir(t_data *data);
int ft_final_parse(t_data *data);

void ft_add_elem(t_data *data, t_list *elem);
char *ft_get_name(char **line, int *i, t_data *data, int flag);
void ft_readline(char *end_word, int *fd);
int ft_skip_quotes(char *line, int i);

int	ft_parse_single_quotes(char **line, int i);
int	ft_parse_double_quotes(char **line, int i, t_data *data, int flag);
int	ft_parse_variables(char **line, int i, char **env, char *status_var);

int ft_cut_line_io_redir(char **line, int i, int j);

/* free */

void ft_close_fd(t_list *list);
void ft_free_path(char **path);
void ft_free_list(t_list *list);

#endif