#include "minishell.h"

int ft_input_redir(t_list *head, int i, t_data *data)
{
	int file;
	int j;
	char *name;

	j = i;
	i++;
	name = ft_get_name(&(head->line), &i, data, WITH_VARIABLES);
	if (!name || !*name)
	{
		//TODO error management: nome file invalido
	}
	file = open(name, O_RDONLY);
	if (file == -1)
	{
		//TODO error: file openining
	}
	if (head->fd_in != -1)
		close(head->fd_in);
	head->fd_in = file;
	return (ft_cut_line_io_redir(&(head->line), i, j));
}

int ft_output_redir(t_list *head, int i, t_data *data)
{
	int file;
	char *name;
	int j;

	j = i;
	i++;
	name = ft_get_name(&(head->line), &i, data, WITH_VARIABLES);
	if (!name || !*name)
	{
		//TODO error management: nome file invalido
	}
	file = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
	{
		//TODO error: file openining
	}
	if (head->fd_out != -1)
		close(head->fd_out);
	head->fd_out = file;
	return (ft_cut_line_io_redir(&(head->line), i, j));
}

int ft_double_output_redir(t_list *head, int i, t_data *data)
{
	int file;
	int j;
	char *name;

	j = i;
	i += 2;
	name = ft_get_name(&(head->line), &i, data, WITH_VARIABLES);
	if (!name || !*name)
	{
		//TODO error management: nome file invalido
	}
	file = open(name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (file == -1)
	{
		//TODO error: file can't be opened
	}
	if (head->fd_out != -1)
		close(head->fd_out);
	head->fd_out = file;
	return (ft_cut_line_io_redir(&(head->line), i, j));
}

int ft_double_input_redir(t_list *head, int i)
{
	char *end_word;
	int j;
	int fd[2];

	if (pipe(fd))
	{
		//TODO error: pipe failed
	}
	j = i;
	i += 2;
	end_word = ft_get_name(&(head->line), &i, 0, NO_VARIABLES);
	ft_readline(end_word, fd);
	free(end_word);
	close(fd[1]);
	if (head->fd_in != -1)
		close(head->fd_in);
	head->fd_in = fd[0];
	return (ft_cut_line_io_redir(&(head->line), i, j));
}

int ft_parse_ioredir(t_data *data)
{
	t_list *head;
	int i;

	head = data->list;
	while (head)
	{
		i = 0;
		while ((head->line)[i])
		{
			i = ft_skip_quotes(head->line, i);
			if ((head->line)[i] == '>' && (head->line)[i + 1] == '>')
				i = ft_double_output_redir(head, i, data);
			else if ((head->line)[i] == '<' && (head->line)[i + 1] == '<')
				i = ft_double_input_redir(head, i);
			else if ((head->line)[i] == '<')
				i = ft_input_redir(head, i, data);
			else if ((head->line)[i] == '>')
				i = ft_output_redir(head, i, data);
			i++;
		}
		head = head->next;
	}
	return (0);
}
