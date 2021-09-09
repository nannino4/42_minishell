#include "minishell.h"

char *ft_getenv(char *var, char **env)
{
	char *value;
	int i;
	int j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		if (!ft_strncmp(var, env[i], j) && j == ft_strlen(var))
		{
			value = env[i];
			while (*value != '=')
				value++;
			return (++value);
		}
		i++;
	}
	return (0);
}

int	ft_arrlen(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

char **ft_env_creation(char **envp)
{
	char **env;
	int strings;
	int i;

	strings = ft_arrlen(envp);
	env = malloc((strings + 1) * sizeof(void *));
	if (!env)
	{
		// TODO error management: allocation failed
	}
	env[strings] = 0;
	i = 0;
	while (i < strings)
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	return (env);
}

char **ft_add_str_to_arr(char *var, char **env)
{
	char **new_env;
	int strings;
	int i;

	strings = ft_arrlen(env) + 1;
	new_env = malloc((strings + 1) * sizeof(void *));
	if (!new_env)
	{
		// TODO error management: allocation failed
	}
	new_env[strings] = 0;
	i = 0;
	while (i < strings - 1)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(var);
	free(env);
	return (new_env);
}
