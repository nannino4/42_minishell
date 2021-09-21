#include "minishell.h"

void	ft_env(t_data *data)
{
	int		i;

	i = 0;
	while (data->list->split[i])
		i++;
	if (i > 1)
	{
		printf("env: Too many arguments\n");
		exit(1);
	}
	i = 0;
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
	exit(0);
}
