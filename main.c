#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    int pid;
    t_data data;

    argc = 0;
    // data.line = ft_strdup(argv[1]);
    argv = 0;
    data.env = ft_env_creation(envp);
    data.line = readline("# Orders, my Lord? ");
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
            data.line = readline("# Orders, my Lord? ");
            if (data.line && ft_strlen(data.line) > 0)
                add_history(data.line);
        }
    }
    printf("exit\n");
}
