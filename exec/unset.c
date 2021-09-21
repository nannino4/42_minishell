#include "minishell.h"

static int	ft_is_var_valid(char *var)
{
	int		i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (0);
	while (var[i])
	{
		if (var[i] != '_' && !ft_isalnum(var[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_remove_var(char *name, t_data *data)
{
	char	**new_env;
	int		strings;
	int		i;
	int		j;
	int		len;

	strings = ft_arrlen(data->env) - 1;
	new_env = malloc((strings + 1) * sizeof(void *));
	new_env[strings] = 0;
	i = 0;
	j = 0;
	while (data->env[j])
	{
		len = ft_len_var(data->env[j]);
		if (!(!ft_strncmp(name, data->env[j], len) && len == ft_strlen(name)))
		{
			new_env[i] = ft_strdup(data->env[j]);
			i++;
		}
		j++;
	}
	ft_free_arr(data->env);
	data->env = new_env;
}

int	ft_unset(t_data *data)
{
	int		i;
	int		ret;

	ret = 0;
	i = 1;
	while (data->list->split[i])
	{
		if (ft_is_var_valid(data->list->split[i]))
		{
			if (ft_getenv(data->list->split[i], data->env))
				ft_remove_var(data->list->split[i], data);
		}
		else
		{
			printf("unset: `%s': not a valid identifier\n", \
					data->list->split[i]);
			ret = 1;
		}
		i++;
	}
	return (ret);
}
