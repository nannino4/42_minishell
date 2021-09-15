#include "minishell.h"

void	rmv_nl(char *str)
{
	int i;

	i = 0;
	while(str[i++])
	if(str[--i] == '\n')
		str[i] = 0;
}

void	ft_echo(t_data *data)
{
	int rmv_n;
	char **argv;
	int i;

	argv = data->list->split;
	rmv_n = 0;
	i = 1;
	if (ft_strncmp(argv[0], "echo", ft_strlen(argv[0]))\
		&& ft_strlen(argv[0]) == ft_strlen("echo"))
	{
		if (ft_strncmp(argv[1], "-n", ft_strlen(argv[1]))\
			&& ft_strlen(argv[1]) == ft_strlen("-n"))
		{
			rmv_n = 1;
			i++;
		}
		while(argv[i] != 0)
		{
			if (rmv_n)
				rmv_nl(argv[i]);
			printf("%s", argv[i++]);
		}
	}
	exit(1);
}
