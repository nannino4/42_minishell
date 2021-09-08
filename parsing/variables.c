#include "minishell.h"

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
    free(*line);
    *line = new_line;
}

int	ft_check_for_variables(char **line, int i)
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
    value = getenv(tmp);
    free(tmp);
    if (!value)
        value = ft_strdup("");
    ft_switch_var_value(line, value, i, j);
    return (j + ft_strlen(value) - 1);
}
