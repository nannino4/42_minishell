#include "minishell.h"

void	ft_add_elem(t_data *data, t_list *elem)
{
	t_list	*list;

	if (!(data->list))
	{
		data->list = elem;
		return ;
	}
	list = data->list;
	while (list->next)
		list = list->next;
	list->next = elem;
	elem->previous = list;
}

char	*ft_getenv(char *var, char **env)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
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
	int		i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

void	ft_increment_shlvl(t_data *data)
{
	int		shlvl;
	char	*var;
	char	*tmp;

	if (ft_getenv("SHLVL", data->env))
	{
		shlvl = ft_atoi(ft_getenv("SHLVL", data->env));
		shlvl++;
		tmp = ft_itoa(shlvl);
		var = ft_strjoin("SHLVL=", tmp);
		ft_replace_var("SHLVL", var, data->env);
	}
	else
	{
		shlvl = 1;
		tmp = ft_itoa(shlvl);
		var = ft_strjoin("SHLVL=", tmp);
		ft_add_var(var, data);
	}
	free(tmp);
	free(var);
}

void	ft_env_creation(t_data *data, char **envp)
{
	char	**env;
	int		strings;
	int		i;

	strings = ft_arrlen(envp);
	env = malloc((strings + 1) * sizeof(void *));
	env[strings] = 0;
	i = 0;
	while (i < strings)
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	data->env = env;
	ft_increment_shlvl(data);
}
