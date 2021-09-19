#include "minishell.h"

// void ft_exec_child2(char *command, char **argv, char **env)
// {
//     execve(command, argv, env);
//     exit(127);
// }

// void ft_exec_parent2(int pid, char *command)
// {
//     int wstatus;

//     waitpid(pid, &wstatus, 0);
//     free(command);
//     if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) != 127)
//     {
//         exit(WEXITSTATUS(wstatus));
//     }
// }

void ft_exec_child1(t_data *data, char **path)
{
    // int pid;
    char *command;

    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    ft_set_io(data->list);
    if (ft_check_builtin(data->list->split[0]))
        ft_exec_builtin(data->list->split[0], data);
    else if (!ft_strchr((data->list->split)[0], '/') && path)
    {
        while (path && *path)
        {
            command = ft_join_path_and_cmd(*path, data->list->split[0]);
            execve(command, data->list->split, data->env);
            // pid = fork();
            // if (pid == 0)
            // ft_exec_child2(command, data->list->split, data->env);
            // else
            // ft_exec_parent2(pid, command);
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
    if (WIFSIGNALED(wstatus) && (WTERMSIG(wstatus) == SIGINT || WTERMSIG(wstatus) == SIGQUIT))
        printf("\n");
    if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 127)
        printf(HYEL "I apologize my Lord, I could not find your command: " BHBLU "%s\n" RESET, command);
    return (WEXITSTATUS(wstatus));
}

void ft_exec(t_data *data)
{
    int pid;
    char **path;
    t_list *list;
    int ret;

    list = data->list;
    while (data->list && !data->exit_flag)
    {
        if (ft_check_special_builtin(data->list->split[0]))
            ret = ft_exec_special_builtin(data->list->split[0], data);
        else
        {
            path = ft_split(ft_getenv("PATH", data->env), ':');
            pid = fork();
            if (pid == 0)
                ft_exec_child1(data, path);
            else
                ret = ft_exec_parent1(pid, data->list->split[0]);
            ft_free_arr(path);
        }
        ft_close_fd(data->list);
        data->list = data->list->next;
    }
    free(data->status_var);
    data->status_var = ft_itoa(ret);
    ft_free_list(list);
}
