#include "minishell.h"

void	ft_input_redir(char **line, int i)
{
	int file;
	int j;
	int diff;

	j = i;
	i++;
	i = skip_spaces(line, i);
	if (ft_istoken(*line[i]))
	{
		//TODO error: parsing
	}
	file = open(ft_get_name(line, &i), O_RDONLY);
	if (file == -1)
	{
		//TODO error: file openining
	}
	if (dup2(file, STDIN_FILENO) == -1)
	{
		//TODO error: dup2 failed
	}
	close(file);
	diff = i - j;
	ft_cut_line_io_redir(line, i, j);
}

void	ft_output_redir(char **line, int i)
{
	int file;
	int j;
	int diff;

	j = i;
	i++;
	i = skip_spaces(line, i);
	if (ft_istoken(*line[i]))
	{
		//TODO error: parsing
	}
	file = open(ft_get_name(line, &i), O_WRONLY | O_CREAT, 0777);
	if (file == -1)
	{
		//TODO error: file openining
	}
	if (dup2(file, STDOUT_FILENO) == -1)
	{
		//TODO error: dup2 failed
	}
	close(file);
	diff = i - j;
	ft_cut_line_io_redir(line, i, j);
}

void	ft_double_output_redir(char **line, int i)
{
	int file;
	int j;
	int diff;

	j = i;
	i += 2;
	i = skip_spaces(line, i);
	if (ft_istoken(*line[i]))
	{
		//TODO error: parsing
	}
	file = open(ft_get_name(line, &i), O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (file == -1)
	{
		//TODO error: file openining
	}
	if (dup2(file, STDOUT_FILENO) == -1)
	{
		//TODO error: dup2 failed
	}
	close(file);
	diff = i - j;
	ft_cut_line_io_redir(line, i, j);
}

void	ft_double_input_redir(char **line, int i)
{
	//TODO
}

void    ft_check_for_redir(char **line, int i)
{
    if (*line[i] == '>' && *line[i + 1] == '>')
		ft_double_output_redir(line, i);
    else if (*line[i] == '<' && *line[i + 1] == '<')
		ft_double_input_redir(line, i);
    else if (*line[i] == '<')
		ft_input_redir(line, i);
    else if (*line[i] == '>')
		ft_output_redir(line, i);
}
