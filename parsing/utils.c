#include "minishell.h"

int	ft_cut_line_io_redir(char **line, int i, int j)
{
	int		diff;
	int		start;

	start = j;
	diff = i - j;
	while (j < ft_strlen(*line) - diff)
	{
		(*line)[j] = (*line)[j + diff];
		j++;
	}
	(*line)[j] = 0;
	return (start - 1);
}

void	ft_readline(char *end_word, int *fd)
{
	char	*tmp;
	char	*buffer;

	buffer = readline(">");
	while (buffer && !(!ft_strncmp(buffer, end_word, ft_strlen(buffer)) && \
				ft_strlen(buffer) == ft_strlen(end_word)))
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

int	ft_skip_single_quotes(char *line, int i)
{
	int		j;

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

int	ft_skip_double_quotes(char *line, int i)
{
	int		j;

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

int	ft_skip_quotes(char *line, int i)
{
	if (line[i] == '\'')
		i = ft_skip_single_quotes(line, i);
	else if (line[i] == '\"')
		i = ft_skip_double_quotes(line, i);
	return (i);
}
