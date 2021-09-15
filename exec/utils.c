#include "minishell.h"

void ft_set_var(char *name, char *value, t_data *data)
{
    char *var;
    char *tmp;

    tmp = ft_strjoin(name, "=");
    var = ft_strjoin(tmp, value);
    free(tmp);
    if (ft_getenv(name, data->env))
        ft_replace_var(name, var, data->env);
    else
        ft_add_var(var, data);
    free(var);
}

char *ft_join_path_and_cmd(char *path, char *command)
{
    char *tmp;
    char *tmp_command;

    tmp_command = ft_strdup(command);
    tmp = ft_strjoin("/", tmp_command);
    free(tmp_command);
    tmp_command = ft_strjoin(path, tmp);
    free(tmp);
    return (tmp_command);
}

void ft_set_io(t_list *list)
{
    if (list->fd_in != -1)
    {
        if (dup2(list->fd_in, STDIN_FILENO) == -1)
        {
            //TODO error: dup2 failed
        }
        close(list->fd_in);
    }
    if (list->fd_out != -1)
    {
        if (dup2(list->fd_out, STDOUT_FILENO) == -1)
        {
            //TODO error: dup2 failed
        }
        close(list->fd_out);
    }
}
