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
    ft_env_creation(data, envp);
    data->list = 0;
    data->status_var = ft_strdup("0");
    data->exit_flag = 0;
    //TODO increment variable SHLVL
}

int main(int argc, char **argv, char **envp)
{
    t_data data;

    if (argc > 1 && argv)
    {
        //TODO error: too many arguments
        exit(127);
    }
    ft_init_data(&data, envp);
    data.line = ft_strdup("");
    while (data.line && !data.exit_flag)
    {
        free(data.line);
        data.line = readline("# Orders, my Lord? >: ");
        if (data.line && ft_strlen(data.line) > 0)
            add_history(data.line);
        ft_parse_and_execute(&data);
    }
    if (data.line)
        free(data.line);
    printf("\nexit\n");
    exit(ft_atoi(data.status_var));
}
