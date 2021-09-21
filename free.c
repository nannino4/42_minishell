#include "minishell.h"

void	ft_close_fd(t_list *list)
{
	if (list->fd_in != -1)
		close(list->fd_in);
	list->fd_in = -1;
	if (list->fd_out != -1)
		close(list->fd_out);
	list->fd_out = -1;
}

void	ft_free_list(t_data *data)
{
	char	*tmp_line;
	t_list	*tmp_list;
	char	**tmp_split;

	while (data->list)
	{
		ft_close_fd(data->list);
		tmp_split = data->list->split;
		if (tmp_split)
		{
			while (*(data->list->split))
			{
				tmp_line = *(data->list->split);
				(data->list->split)++;
				free(tmp_line);
			}
			free(tmp_split);
		}
		if (data->list->line)
			free(data->list->line);
		tmp_list = data->list;
		data->list = data->list->next;
		free(tmp_list);
	}
	data->list = 0;
}

void	ft_free_arr(char **arr)
{
	char	**tmp;

	tmp = arr;
	while (arr && *arr)
	{
		free(*arr);
		arr++;
	}
	if (tmp)
		free(tmp);
}

void	ft_free_data(t_data *data)
{
	if (data->line)
		free(data->line);
	ft_free_arr(data->env);
	ft_free_list(data);
	free(data->status_var);
}
