#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/param.h>
# include <fcntl.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "libft.h"
# include "color.h"

# define WITH_VARIABLES 1
# define NO_VARIABLES 0
# define READ_END 0
# define WRITE_END 1

typedef struct s_list
{
	struct s_list	*previous;
	struct s_list	*next;
	char			*line;
	char			**split;
	int				fd_out;
	int				fd_in;
}				t_list;

typedef struct s_data
{
	t_list		*list;
	char		*line;
	char		**env;
	char		*status_var;
	int			exit_flag;
}				t_data;

/* utils */

int		ft_istoken(char c);
int		ft_isspace(char c);
int		ft_isquotes(char c);

int		ft_skip_spaces(char *line, int i);
void	ft_env_creation(t_data *data, char **envp);
char	*ft_getenv(char *var, char **env);
int		ft_arrlen(char **arr);

/* exec */

int		ft_exec(t_data *data);
void	ft_set_io(t_list *list);
char	*ft_join_path_and_cmd(char *path, char *command);
void	ft_add_var(char *var, t_data *data);
void	ft_replace_var(char *name, char *var, char **env);
void	ft_set_var(char *var, char *value, t_data *data);
int		ft_len_var(char *var);

int		ft_check_special_builtin(char *command);
int		ft_exec_special_builtin(char *command, t_data *data);
int		ft_check_builtin(char *command);
void	ft_exec_builtin(char *command, t_data *data);
int		ft_unset(t_data *data);
int		ft_exit(t_data *data);
int		ft_export(t_data *data);
void	ft_pwd(void);
void	ft_echo(t_data *data);
void	ft_env(t_data *data);
int		ft_cd(t_data *data);

/* parsing */

int		ft_parse_pipes(t_data *data);
int		ft_parse_ioredir(t_data *data);
int		ft_final_parse(t_data *data);

void	ft_add_elem(t_data *data, t_list *elem);
char	*ft_get_name(char **line, int *i, t_data *data, int flag);
void	ft_readline(char *end_word, int *fd);
int		ft_skip_quotes(char *line, int i);

int		ft_parse_single_quotes(char **line, int i);
int		ft_parse_double_quotes(char **line, int i, t_data *data, int flag);
int		ft_parse_variables(char **line, int i, char **env, char *status_var);

int		ft_get_io_return(int i);
int		ft_cut_line_io_redir(char **line, int i, int j);

/* free */

void	ft_close_fd(t_list *list);
void	ft_free_arr(char **arr);
void	ft_free_list(t_data *data);
void	ft_free_data(t_data *data);

void	ft_error_exit(int n, char *str);
int		ft_error(int n, char *str);
int		ft_error_and_free(int n, char *str, t_data *data);

#endif
