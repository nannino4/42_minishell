#include "minishell.h"

/*
** ft_get_name takes line as input, and gives back the first word before spaces or tokens, setting "i" at the end 
*/

char	*ft_get_name(char *line, int *i)
{
	int	start;

	*i = ft_skip_spaces(line, *i);
	start = *i;
	while (line[*i] && !ft_istoken(line[*i]) && line[*i] != ' ')
	{
		if (line[*i] == '\'')
			*i = ft_check_for_single_quotes(&line, start);
		else if (line[*i] == '\"')
			*i = ft_check_for_double_quotes(&line, start);
		//  
		// 	*i = ft_check_for_variables(&line, start);
		(*i)++;
	}
	return (ft_substr(line, start, *i - start));
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
