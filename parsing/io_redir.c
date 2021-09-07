#include "minishell.h"

void	ft_input_redir(char **line, int i)
{
	int file;
	int j;
	int diff;
	char *name;

	j = i;
	i++;
	name = ft_get_name(*line, &i);
	if (!name || !*name)
	{
		//TODO error management: nome file invalido
	}
	file = open(name, O_RDONLY);
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
	char *name;
	int j;

	j = i;
	i++;
	name = ft_get_name(*line, &i);
	if (!name || !*name)
	{
		//TODO error management: nome file invalido
	}
	file = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
	{
		//TODO error: file openining
	}
	if (dup2(file, STDOUT_FILENO) == -1)
	{
		//TODO error: dup2 failed
	}
	close(file);
	ft_cut_line_io_redir(line, i, j);
}

void	ft_double_output_redir(char **line, int i)
{
	int file;
	int j;
	int diff;
	char *name;

	j = i;
	i += 2;
	name = ft_get_name(*line, &i);
	if (!name || !*name)
	{
		//TODO error management: nome file invalido
	}
	file = open(name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (file == -1)
	{
		//TODO error: file can't be opened
	}
	if (dup2(file, STDOUT_FILENO) == -1)
	{
		//TODO error: dup2 failed
	}
	close(file);
	diff = i - j;
	ft_cut_line_io_redir(line, i, j);
}

// void	ft_double_input_redir(char **line, int i)
// {
// 	//TODO
// }

int    ft_check_for_redir(char **line, int i)
{
    if ((*line)[i] == '>' && *line[i + 1] == '>')
		ft_double_output_redir(line, i);
    // else if ((*line)[i] == '<' && *line[i + 1] == '<')
	// 	ft_double_input_redir(line, i);
    else if ((*line)[i] == '<')
		ft_input_redir(line, i);
    else if ((*line)[i] == '>')
		ft_output_redir(line, i);
	return (i); //TODO controlla output i
}
