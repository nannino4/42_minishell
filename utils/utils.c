#include "minishell.h"

/*
** ft_get_name takes line as input, and gives back the first word before spaces or tokens, setting "i" at the end 
*/

char	*ft_get_name(char *line, int *i)
{
	int	start;

	*i = ft_skip_spaces(line, *i);
	start = *i;
	while (line[*i] && !ft_istoken(line[*i]) && line[*i] != ' ')
	{
		if (line[start] == '\'')
			*i = ft_check_for_single_quotes(&line, start);
		else if (line[start] == '\"')
			*i = ft_check_for_double_quotes(&line, start);
		(*i)++;
	}
	return (ft_substr(line, start, *i - start));
}

int	ft_skip_spaces(char *line, int i)
{
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

int	ft_istoken(char c)
{
	if (c == '~' || c == '#' || c == '%' || c == '&' || c == '*' || c == '{' || c == '}' || c == '\\' || c == ':' || c == '<' || c == '>' || c == '?' || c == '/' || c == '|')
	{
		return (1);
	}
	return (0);
}
