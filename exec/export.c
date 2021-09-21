#include "minishell.h"

static int	ft_is_var_valid(char *var)
{
	int		i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (0);
	while (var[i] && var[i] != '=')
	{
		if (var[i] != '_' && !ft_isalnum(var[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_add_var(char *var, t_data *data)
{
	char	**new_env;
	int		strings;
	int		i;

	strings = ft_arrlen(data->env) + 1;
	new_env = malloc((strings + 1) * sizeof(void *));
	new_env[strings] = 0;
	i = 0;
	while (i < strings - 1)
	{
		new_env[i] = ft_strdup(data->env[i]);
		i++;
	}
	new_env[i] = ft_strdup(var);
	ft_free_arr(data->env);
	data->env = new_env;
}

int	ft_len_var(char *var)
{
	int		i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

void	ft_set_ret_to_1(int *ret, char *arg)
{
	printf("export: `%s': not a valid identifier\n", arg);
	*ret = 1;
}

int	ft_export(t_data *data)
{
	int		i;
	int		ret;
	char	*name;

	ret = 0;
	i = 0;
	while (data->list->split[++i])
	{
		if (ft_is_var_valid(data->list->split[i]))
		{
			if (ft_strchr(data->list->split[i], '='))
			{
				name = ft_substr(data->list->split[i], 0, \
						ft_len_var(data->list->split[i]));
				if (ft_getenv(name, data->env))
					ft_replace_var(name, data->list->split[i], data->env);
				else
					ft_add_var(data->list->split[i], data);
				free(name);
			}
		}
		else
			ft_set_ret_to_1(&ret, data->list->split[i]);
	}
	return (ret);
}
