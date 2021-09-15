#include "minishell.h"

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
    if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) != 127)
    {
        exit(WEXITSTATUS(wstatus));
    }
}

void ft_exec_child1(t_data *data, char **path)
{
    int pid;
    char *command;

    ft_set_io(data->list);
    // if (ft_check_builtin(data->list->split[0]))
    //     ft_exec_builtin(data->list->split[0], data);
    if (!ft_strchr((data->list->split)[0], '/') && path)
    {
        while (path && *path)
        {
            command = ft_join_path_and_cmd(*path, data->list->split[0]);
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

int ft_exec_parent1(int pid, char *command)
{
    int wstatus;

    waitpid(pid, &wstatus, 0);
    if (WEXITSTATUS(wstatus) == 127)
        printf(HYEL"I apologize my Lord, I could not find your command: "BHBLU"%s\n"RESET, command);
    return (wstatus);
}

void ft_exec(t_data *data)
{
    int pid;
    char **path;
    t_list *list;
    int wstatus;

    list = data->list;
    while (data->list)
    {
        path = ft_split(ft_getenv("PATH", data->env), ':');
        pid = fork();
        if (pid == 0)
            ft_exec_child1(data, path);
        else
            wstatus = ft_exec_parent1(pid, data->list->split[0]);
        ft_close_fd(data->list);
        data->list = data->list->next;
        ft_free_path(path);
    }
    ft_free_list(list);
    free(data->status_var);
    data->status_var = ft_itoa(WEXITSTATUS(wstatus));
    exit(WEXITSTATUS(wstatus));
}
