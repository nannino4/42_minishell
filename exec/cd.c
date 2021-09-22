#include "minishell.h"

int	ft_cd(t_data *data)
{
	char	*old_pwd;
	char	*pwd;
	char	*tmp;

	tmp = getcwd(0, 0);
	old_pwd = ft_strjoin("OLDPWD=", tmp);
	free(tmp);
	if (chdir(data->list->split[1]))
	{
		printf("cd: %s: %s\n", data->list->split[1], strerror(errno));
		free(old_pwd);
		return (1);
	}
	tmp = getcwd(0, 0);
	pwd = ft_strjoin("PWD=", tmp);
	free(tmp);
	if (ft_getenv("OLDPWD", data->env))
		ft_replace_var("OLDPWD", old_pwd, data->env);
	if (ft_getenv("PWD", data->env))
		ft_replace_var("PWD", pwd, data->env);
	free(old_pwd);
	free(pwd);
	return (0);
}
