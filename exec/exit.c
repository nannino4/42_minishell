#include "minishell.h"

int	ft_exit(t_data *data)
{
	int		i;

	if (ft_arrlen(data->list->split) > 2)
	{
		printf("exit: too many arguments\n");
		return (1);
	}
	i = 0;
	data->exit_flag = 1;
	if (ft_arrlen(data->list->split) == 2)
	{
		while (data->list->split[1][i])
		{
			if (!ft_isdigit(data->list->split[1][i]))
			{
				printf("exit: %s: positive numeric argument required\n", \
						data->list->split[1]);
				return (255);
			}
			i++;
		}
		return (ft_atoi(data->list->split[1]));
	}
	return (0);
}
