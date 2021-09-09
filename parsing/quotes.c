#include "minishell.h"

int	ft_check_for_single_quotes(char **line, int i)
{
	int j;

	j = i;
	while ((*line)[++i])
	{
		if ((*line)[i] == '\'')
		{
			return (ft_cut_line_quotes(line, i, j));
		}
	}
	return (j);
}

int	ft_check_for_double_quotes(char **line, int i, char **env)
{
	int j;

	j = i;
	while ((*line)[++i])
	{
		if ((*line)[i] == '$')
		{
			ft_check_for_variables(line, i, env);
		}
		if ((*line)[i] == '\"')
		{
			return (ft_cut_line_quotes(line, i, j));
		}
	}
	return (j);
}
