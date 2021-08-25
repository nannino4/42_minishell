#include "minishell.h"

int	ft_check_for_single_quotes(char **line, int i)
{
	int j;

	j = i;
	while (*line[++i])
	{
		if (*line[i] == '\'')
		{
			while (j < i - 1)
			{
				*line[j] = *line[j + 1];
				j++;
			}
			while (j < strlen(*line) - 2)
			{
				*line[j] = *line[j + 2];
				j++;
			}
			*line[j] = 0;
			return (i - 2);
		}
	}
	return (j);
}

int	ft_check_for_double_quotes(char **line, int i)
{
	int j;

	j = i;
	while (*line[++i])
	{
		if (*line[i] == '$')
			ft_check_for_variables(line, i);
		if (*line[i] == '\"')
		{
			while (j < i - 1)
			{
				*line[j] = *line[j + 1];
				j++;
			}
			while (j < strlen(*line) - 2)
			{
				*line[j] = *line[j + 2];
				j++;
			}
			*line[j] = 0;
			return (i - 2);
		}
	}
	return (j);
}

int	ft_istoken(char c)
{
	if (c == '~' || c == '#' || c == '%' || c == '&' || c == '*' || c == '{' || c == '}' || c == '\\' || c == ':' || c == '<' || c == '>' || c == '?' || c == '/' || c == '|' || c == '"' || c == '\'')
	{
		return (1);
	}
	return (0);
}

void	ft_input_redir(char **line, int i)
{
	int file;
	int j;

	j = i;
	i++;
	i = skip_spaces(line, i);
	if (ft_istoken(*line[i]))
	{
		//TODO error: parsing
	}
	file = open(ft_get_name(line, i), O_RDONLY);
	if (file == -1)
	{
		//TODO error: file openining
	}
	if (dup2(file, STDIN_FILENO) == -1)
	{
		//TODO error: dup2 failed
	}
	
}

void    ft_check_for_redir(char **line, int i)
{
    if (*line[i] == '<')
    {
		ft_input_redir(line, i);
	}
    else if (*line[i] == '>')
	{
		ft_output_redir(line, i);
	}
    else if (*line[i] == '<<')
	{
		ft_double_input_redir(line, i);
	}
    else if (*line[i] == '>>')
	{
		ft_double_output_redir(line, i);
	}
}
