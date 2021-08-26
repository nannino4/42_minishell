#include "minishell.h"

int	ft_cut_line_quotes(char **line, int i, int j)
{
	while (j < i - 1)
	{
		*line[j] = *line[j + 1];
		j++;
	}
	while (j < ft_strlen(*line) - 2)
	{
		*line[j] = *line[j + 2];
		j++;
	}
	*line[j] = 0;
	return (i - 2);
}

void	ft_cut_line_io_redir(char **line, int i, int j)
{
	int diff;

	diff = i - j;
	while (j < ft_strlen(*line) - diff)
	{
		*line[j] = *line[j + diff];
		j++;
	}
	*line[j] = 0;
}
