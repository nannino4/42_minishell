#include "minishell.h"

int ft_parse_and_execute(t_data *data)
{
    int ret;

    ret = ft_parse_pipes(data);
    if (ret)
        return (ret);
    ret = ft_parse_ioredir(data);
    if (ret)
        return (ret);
    ret = ft_final_parse(data);
    if (ret)
        return (ret);
    return (ft_exec(data));
}

void ft_init(t_data *data, char **envp)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    ft_env_creation(data, envp);
    data->line = ft_strdup("");
    data->list = 0;
    data->status_var = ft_strdup("0");
    data->exit_flag = 0;
}

int main(int argc, char **argv, char **envp)
{
    t_data data;
    int status;

    if (argc > 1 && argv)
        ft_error_exit(127, "./minishell: too many arguments");
    ft_init(&data, envp);
    while (data.line && !data.exit_flag)
    {
        ft_free_list(data.list);
        free(data.line);
        printf(BHBLU"––––––––––––\n"RESET);
        data.line = readline("# ORDERS, MY LORD >: ");
        if (data.line && *(data.line))
        {
            add_history(data.line);
            free(data.status_var);
            data.status_var = ft_itoa(ft_parse_and_execute(&data));
        }
    }
    printf("exit\n");
    status = ft_atoi(data.status_var);
    ft_free_data(data);
    exit(status);
}
