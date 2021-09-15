#include "minishell.h"

void ft_parse_and_execute(t_data *data)
{
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
        ft_exec(data);
    }
}

void ft_init_data(t_data *data, char **envp)
{
    data->env = ft_env_creation(envp);
    data->line = readline("# Orders, my Lord? >: ");
    data->list = 0;
    data->status_var = ft_strdup("0");
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
            ft_parse_and_execute(&data);
        else
        {
            wait(0);
            free(data.line);
            data.line = readline("# Orders, my Lord? >: ");
            if (data.line && ft_strlen(data.line) > 0)
                add_history(data.line);
        }
    }
    printf("\nexit\n");
}
