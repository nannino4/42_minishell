#include "minishell.h"

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

void ft_exec_child2(char *command, char **argv, char **env)
{
    execve(command, argv, env);
    exit(127);
}

void ft_exec_parent2(int pid, char *command)
{
    int wstatus;

    waitpid(pid, &wstatus, 0);
    free(command);
    if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) != 0)
        exit(WEXITSTATUS(wstatus));
}

int ft_exec_child1(t_data *data, char **path)
{
    int pid;
    char *command;

    ft_set_io(data->list);
    if (!ft_strchr((data->list->split)[0], '/') && path)
    {
        while (path && *path)
        {
            command = ft_strjoin(*path, data->list->split[0]);
            pid = fork();
            if (pid == 0)
                ft_exec_child2(command, data->list->split, data->env);
            else
                ft_exec_parent2(pid, command);
            path++;
        }
    }
    else
        execve((data->list->split)[0], (data->list->split), data->env);
    exit(127);
}

void ft_exec_parent1(int pid, char *command, char **path, t_list *list)
{
    int wstatus;

    waitpid(pid, &wstatus, 0);
    // ft_set_var("?", WEXITSTATUS(wstatus));
    if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) != 0)
    {
        if (WEXITSTATUS(wstatus) == 127)
            printf("I apologize my Lord, I could not find you command: %s\nSpare my life, I beg you..\n", command);
        ft_free_split(path);
        ft_free_list(list);
        exit(WEXITSTATUS(wstatus));
    }
}

void ft_exec(t_data *data)
{
    int pid;
    char **path;
    t_list *list;

    list = data->list;
    while (data->list)
    {
        path = ft_split(ft_getenv("PATH", data->env), ':');
        pid = fork();
        if (pid == 0)
            ft_exec_child1(data, path);
        else
            ft_exec_parent1(pid, data->list->split[0], path, list);
        data->list = data->list->next;
        ft_free_split(path);
    }
    ft_free_list(list);
}
