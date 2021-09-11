#include "minishell.h"

int ft_isquotes(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_skip_spaces(char *line, int i)
{
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

int	ft_istoken(char c)
{
	if (c == '~' || c == '#' || c == '&' || c == '*' || c == '\\' || c == '<' || c == '>' || c == '/' || c == '|')
	{
		return (1);
	}
	return (0);
}
