#include "minishell.h"

void sigquit_handler()
{
    rl_on_new_line();
    rl_redisplay();
    ft_putstr_fd("  \b\b", 1);
}

void ft_parse_and_execute(t_data *data)
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

void ft_read(t_data data)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, sigquit_handler);
    data.line = readline("# Orders, my Lord? >: ");
    if (data.line)
    {
        if (!*(data.line))
            ft_putstr_fd("\n", data.fd[WRITE_END]);
        else
            ft_putstr_fd(data.line, data.fd[WRITE_END]);
        free(data.line);
    }
    exit(0);
}

void ft_start(t_data *data)
{
    wait(&data->wstatus);
    if (WIFSIGNALED(data->wstatus) && WTERMSIG(data->wstatus) == SIGINT)
    {
        ft_putstr_fd("\n", data->fd[WRITE_END]);
        printf("\n");
    }
    if (WIFSIGNALED(data->wstatus) && WTERMSIG(data->wstatus) == SIGQUIT)
    {
        printf("ft_read e' stata uccisa da SIGQUIT\n");
    }
    close(data->fd[WRITE_END]);
    data->line = ft_getstr_fd(data->fd[READ_END]);
    close(data->fd[READ_END]);
    if (data->line && *(data->line) > 0)
    {
        add_history(data->line);
        ft_parse_and_execute(data);
    }
}

int main(int argc, char **argv, char **envp)
{
    t_data data;

    if (argc > 1 && argv)
    {
        //TODO error: too many arguments
        exit(127);
    }
    ft_init(&data, envp);
    while (data.line && !data.exit_flag)
    {
        free(data.line);
        pipe(data.fd);
        data.pid = fork();
        if (data.pid == 0)
            ft_read(data);
        else
            ft_start(&data);
    }
    if (data.line)
        free(data.line);
    printf("exit\n");
    exit(ft_atoi(data.status_var));
}
