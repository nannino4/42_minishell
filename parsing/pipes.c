#include "minishell.h"

int	ft_cut_pipe(t_data *data, char **line, int i)
{
	t_list	*elem;
	int		fd[2];

	elem = malloc(sizeof(t_list));
	elem->line = ft_substr(*line, 0, i);
	elem->fd_in = -1;
	elem->fd_out = -1;
	elem->split = 0;
	elem->next = 0;
	elem->previous = 0;
	ft_add_elem(data, elem);
	if (elem->previous)
	{
		if (pipe(fd))
			return (ft_error(-1, "piping failed: pipe creation failed"));
		elem->fd_in = fd[0];
		elem->previous->fd_out = fd[1];
	}
	while (**line && **line != '|')
		(*line)++;
	if (**line == '|')
		(*line)++;
	return (0);
}

int	ft_return_pipes(int word_flag, t_data *data, char *line, int i)
{
	if (!word_flag)
		return (ft_error(258, "line ending with unexpected '|'"));
	return (ft_cut_pipe(data, &line, i));
}

int	ft_parse_pipes(t_data *data)
{
	int		word_flag;
	int		i;
	char	*line;

	word_flag = 0;
	i = 0;
	line = data->line;
	while (line[i])
	{
		i = ft_skip_quotes(line, i);
		if (line[i] != '|' && !ft_isspace(line[i]))
			word_flag = 1;
		else if (line[i] == '|')
		{
			if (!word_flag)
				return (ft_error(258, "unexpected '|'"));
			word_flag = 0;
			if (ft_cut_pipe(data, &line, i))
				return (-1);
			i = -1;
		}
		i++;
	}
	return (ft_return_pipes(word_flag, data, line, i));
}
