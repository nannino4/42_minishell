#include "minishell.h"

void	ft_error_exit(int n, char *str)
{
	ft_error(n, str);
	exit(n);
}

int	ft_error(int n, char *str)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (n);
}
