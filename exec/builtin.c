#include "minishell.h"

int	ft_check_special_builtin(char *command)
{
	if (!ft_strncmp(command, "cd", ft_strlen(command)) && \
			ft_strlen(command) == ft_strlen("cd"))
		return (1);
	if (!ft_strncmp(command, "export", ft_strlen(command)) && \
			ft_strlen(command) == ft_strlen("export"))
		return (1);
	else if (!ft_strncmp(command, "unset", ft_strlen(command)) \
			&& ft_strlen(command) == ft_strlen("unset"))
		return (1);
	else if (!ft_strncmp(command, "exit", ft_strlen(command)) \
			&& ft_strlen(command) == ft_strlen("exit"))
		return (1);
	return (0);
}

int	ft_exec_special_builtin(char *command, t_data *data)
{
	if (!ft_strncmp(command, "cd", ft_strlen(command)) && \
			ft_strlen(command) == ft_strlen("cd"))
		return (ft_cd(data));
	else if (!ft_strncmp(command, "export", ft_strlen(command)) && \
			ft_strlen(command) == ft_strlen("export"))
		return (ft_export(data));
	else if (!ft_strncmp(command, "unset", ft_strlen(command)) && \
			ft_strlen(command) == ft_strlen("unset"))
		return (ft_unset(data));
	else if (!ft_strncmp(command, "exit", ft_strlen(command)) && \
			ft_strlen(command) == ft_strlen("exit"))
		return (ft_exit(data));
	return (127);
}

int	ft_check_builtin(char *command)
{
	if (!ft_strncmp(command, "echo", ft_strlen(command)) && \
			ft_strlen(command) == ft_strlen("echo"))
		return (1);
	else if (!ft_strncmp(command, "pwd", ft_strlen(command)) && \
			ft_strlen(command) == ft_strlen("pwd"))
		return (1);
	else if (!ft_strncmp(command, "env", ft_strlen(command)) && \
			ft_strlen(command) == ft_strlen("env"))
		return (1);
	return (0);
}

void	ft_exec_builtin(char *command, t_data *data)
{
	if (!ft_strncmp(command, "echo", ft_strlen(command)) && \
			ft_strlen(command) == ft_strlen("echo"))
		ft_echo(data);
	else if (!ft_strncmp(command, "pwd", ft_strlen(command)) && \
			ft_strlen(command) == ft_strlen("pwd"))
		ft_pwd();
	else if (!ft_strncmp(command, "env", ft_strlen(command)) && \
			ft_strlen(command) == ft_strlen("env"))
		ft_env(data);
}
