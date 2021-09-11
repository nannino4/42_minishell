#include "minishell.h"

int	ft_parse_single_quotes(char **line, int i)
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

int	ft_parse_double_quotes(char **line, int i, char **env, int flag)
{
	int j;

	j = i;
	while ((*line)[++i])
	{
		if (flag && (*line)[i] == '$' && ft_strchr(*line + i, '\"'))
		{
			ft_parse_variables(line, i, env);
		}
		if ((*line)[i] == '\"')
		{
			return (ft_cut_line_quotes(line, i, j));
		}
	}
	return (j);
}

void    ft_switch_var_value(char **line, char *value, int i, int j)
{
    char *new_line;
    int k;
    int len_tmp;

    new_line = malloc(j + ft_strlen(value) + ft_strlen(*line) - i + 1);
    k = 0;
    while (k < j)
    {
        new_line[k] = (*line)[k];
        k++;
    }
    k = 0;
    len_tmp = ft_strlen(value);
    while (k < len_tmp)
    {
        new_line[j + k] = value[k];
        k++;
    }
    len_tmp = ft_strlen(*line);
    while (i < len_tmp)
        new_line[j + k++] = (*line)[i++];
    new_line[j + k] = 0;
    free(*line);
    *line = new_line;
}

int	ft_parse_variables(char **line, int i, char **env)
{
	int j;
    int len;
    char *tmp;
    char *value;

    j = i;
    i++;
    while ((*line)[i] && !ft_isspace((*line)[i]) && !ft_istoken((*line)[i]) && !ft_isquotes((*line)[i]))
        i++;
    len = i - j - 1;
    if (len == 0)
        return (i);
    tmp = ft_substr(*line, j + 1, len);
    // value = "gcefalo";
    value = ft_getenv(tmp, env);
    free(tmp);
    if (!value)
        value = ft_strdup("");
    ft_switch_var_value(line, value, i, j);
    return (j + ft_strlen(value) - 1);
}
