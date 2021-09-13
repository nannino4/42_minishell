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
    printf("\nsono in ft_set_io\ncommand = %s\nfd_in = %d\nfd_out = %d\n\n", (list->split)[0], list->fd_in, list->fd_out);
}

void ft_exec_commands(t_data *data)
{
    int pid;
    char *path;

    path = ft_getenv("PATH", data->env);
    while (data->list)
    {
        pid = fork();
        if (pid == 0)
        {
            ft_set_io(data->list);
            if (!ft_strchr((data->list->split)[0], '/') && path)
            {
                // TODO cerca nel path ed esegui
            }
            else
            {
                execve((data->list->split)[0], (data->list->split), data->env);
                printf("execve non ha funzionato\n");
            }
            exit(0);
        }
        else
        {
            wait(0);
            data->list = data->list->next;
        }
    }
}

void ft_parse_and_execute(t_data *data)
{
    // char **split;

    if (*(data->line))
    {
        if (ft_parse_pipes(data))
        {
            //TODO error: pipes error
        }
        if (ft_parse_ioredir(data))
        {
            //TODO error: ioredir error
        }
        if (ft_final_parse(data))
        {
            //TODO error: final parse error
        }
        ft_exec_commands(data);
        // while (data->list)
        // {
        //     split = data->list->split;
        //     while (*split)
        //     {
        //         printf("%p %s\n", data->list, *split);
        //         split++;
        //     }
        //     data->list = data->list->next;
        // }
        ft_free_list(data->list);
    }
}

void ft_init_data(t_data *data, char **envp)
{
    data->env = ft_env_creation(envp);
    data->line = readline("# Orders, my Lord? >:");
    data->list = 0;
    data->local_env = 0;
}

int main(int argc, char **argv, char **envp)
{
    int pid;
    t_data data;

    if (argc > 1)
    {
        //TODO error: too many arguments
    }
    // data.line = ft_strdup(argv[1]);
    argv = 0;
    ft_init_data(&data, envp);
    if (data.line && ft_strlen(data.line) > 0)
        add_history(data.line);
    while (data.line)
    {
        pid = fork();
        if (pid == 0)
        {
            ft_parse_and_execute(&data);
            exit(0);
        }
        else
        {
            wait(0);
            free(data.line);
            data.line = readline("# Orders, my Lord? >:");
            if (data.line && ft_strlen(data.line) > 0)
                add_history(data.line);
        }
    }
    printf("\nexit\n");
}
