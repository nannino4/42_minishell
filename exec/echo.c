#include "minishell.h"

void	ft_echo(t_data *data)
{
	int rmv_n;
	char **argv;
	int i;

	argv = data->list->split;
	rmv_n = 0;
	i = 1;
		if (!ft_strncmp(argv[1], "-n", ft_strlen(argv[1]))\
			&& ft_strlen(argv[1]) == ft_strlen("-n"))
		{
			rmv_n = 1;
			i++;
		}
		while(argv[i])
		{
			printf("%s", argv[i]);
			i++;
		}
		if (!rmv_n)
			printf("\n");
	exit(0);
}
