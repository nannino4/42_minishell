#include "minishell.h"

int	ft_cut_line_quotes(char **line, int i, int j)
{
	while (j < i - 1)
	{
		(*line)[j] = (*line)[j + 1];
		j++;
	}
	while (j < ft_strlen(*line) - 2)
	{
		(*line)[j] = (*line)[j + 2];
		j++;
	}
	(*line)[j] = 0;
	return (i - 2);
}

void	ft_cut_line_io_redir(char **line, int i, int j)
{
	int diff;

	diff = i - j;
	while (j < ft_strlen(*line) - diff)
	{
		(*line)[j] = (*line)[j + diff];
		j++;
	}
	(*line)[j] = 0;
}

void ft_add_elem(t_list *head, t_list *elem)
{
	//TODO
}

char *ft_get_name(char **line, int *i, char **env, int flag)
{
	int start;

	*i = ft_skip_spaces(*line, *i);
	start = *i;
	while ((*line)[*i] && !ft_istoken((*line)[*i]) && (*line)[*i] != ' ')
	{
		if ((*line)[*i] == '\'')
			*i = ft_parse_single_quotes(line, *i);
		else if ((*line)[*i] == '\"')
			*i = ft_parse_double_quotes(line, *i, env, flag);
		else if (flag && (*line)[*i] == '$')
			*i = ft_parse_variable(line, *i, env);
		(*i)++;
	}
	return (ft_substr(*line, start, *i - start));
}

void ft_readline(char *end_word, int *fd)
{
	char *tmp;
	char *buffer;

	buffer = readline(">");
	while (buffer && !(!ft_strncmp(buffer, end_word, ft_strlen(buffer)) && ft_strlen(buffer) == ft_strlen(end_word)))
	{
		tmp = ft_strjoin(buffer, "\n");
		free(buffer);
		buffer = tmp;
		ft_putstr_fd(buffer, fd[1]);
		free(buffer);
		buffer = readline(">");
	}
	if (buffer)
		free(buffer);
}

int ft_skip_single_quotes(char *line, int i)
{
    int j;

    j = 0;
    i++;
    while (line[i])
    {
        if (line[i] == '\'')
            return (i);
        i++;
    }
    return (j);
}

int ft_skip_double_quotes(char *line, int i)
{
    int j;

    j = 0;
    i++;
    while (line[i])
    {
        if (line[i] == '\"')
            return (i);
        i++;
    }
    return (j);
}

int ft_skip_quotes(char *line, int i)
{
    if (line[i] == '\'')
        i = ft_skip_single_quotes(line, i);
    else if (line[i] == '\"')
        i = ft_skip_double_quotes(line, i);
    return(i);
}
