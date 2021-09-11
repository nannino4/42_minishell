#include "minishell.h"

void ft_cut_pipe(t_data *data, int i)
{
	t_list *elem;
	int fd[2];

	elem = malloc(sizeof(t_list));
	elem->line = ft_substr(data->line, 0, i);
	elem->fd_in = -1;
	elem->fd_out = -1;
	ft_add_elem(data->list, elem);
	if (elem->previous)
	{
		if (pipe(fd))
		{
			//TODO error: pipe creation
		}
		elem->fd_in = fd[0];
		elem->previous->fd_out = fd[1];
	}
	while (*(data->line) != '|')
	{
		(data->line)++;
	}
	(data->line)++;
}

int ft_parse_pipes(t_data *data)
{
	int word_flag;
	int i;

	word_flag = 0;
	i = 0;
	while ((data->line)[i])
	{
		i = ft_skip_quotes(data->line, i);
		if (!ft_isspace((data->line)[i]))
			word_flag = 1;
		else if ((data->line)[i] == '|')
		{
			if (!word_flag)
			{
				// TODO error: unexpected '|'
			}
			word_flag = 0;
			ft_cut_pipe(data, i);
			i = -1;
		}
		i++;
	}
	if (!word_flag)
	{
		// TODO error: line ending with unexpected '|'
	}
	ft_cut_pipe(data, i);
	return (0);
}
