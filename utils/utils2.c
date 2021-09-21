#include "minishell.h"

char	*ft_get_name(char **line, int *i, t_data *data, int flag)
{
	int		start;
	int		is_valid;

	is_valid = 0;
	*i = ft_skip_spaces(*line, *i);
	start = *i;
	while ((*line)[*i] && !ft_istoken((*line)[*i]) && (*line)[*i] != ' ')
	{
		is_valid = 1;
		if ((*line)[*i] == '\'')
			*i = ft_parse_single_quotes(line, *i);
		else if ((*line)[*i] == '\"')
			*i = ft_parse_double_quotes(line, *i, data, flag);
		else if (flag && (*line)[*i] == '$')
			*i = ft_parse_variables(line, *i, data->env, data->status_var);
		(*i)++;
	}
	if (!is_valid)
		return (0);
	return (ft_substr(*line, start, *i - start));
}

int	ft_isquotes(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_skip_spaces(char *line, int i)
{
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

int	ft_istoken(char c)
{
	if (c == '~' || c == '#' || c == '&' || c == '*' || c == '\\' || c == '<' \
			|| c == '>' || c == '/' || c == '|')
	{
		return (1);
	}
	return (0);
}
