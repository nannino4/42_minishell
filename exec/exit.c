#include "minishell.h"

void ft_exit(t_data *data)
{
    int i;

    if (ft_arrlen(data->list->split) > 2)
    {
        //TODO error: exit: too many arguments
        exit(1);
    }
    i = 0;
    data->exit_flag = 1;
    while (data->list->split[1][i])
    {
        if (!ft_isdigit(data->list->split[1][i]))
        {
            //TODO error: exit: numeric argument required
            exit(255);
        }
        i++;
    }
    exit(ft_atoi(data->list->split[1]));
}
