#include "minishell.h"

int ft_exit(t_data *data)
{
    int i;

    if (ft_arrlen(data->list->split) > 2)
    {
        //TODO error: exit: too many arguments
        return (1);
    }
    i = 0;
    data->exit_flag = 1;
    while (data->list->split[1][i])
    {
        if (!ft_isdigit(data->list->split[1][i]))
        {
            //TODO error: exit: numeric argument required
            return (255);
        }
        i++;
    }
    return (ft_atoi(data->list->split[1]));
}
