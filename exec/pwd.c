#include "minishell.h"

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(0, 0);
	if (!pwd)
	{
		perror("pwd: Error: ");
		exit(1);
	}
	printf("%s\n", pwd);
	free(pwd);
	exit(0);
}
