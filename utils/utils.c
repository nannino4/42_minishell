#include "minishell.h"

int	ft_istoken(char c)
{
	if (c == '~' || c == '#' || c == '%' || c == '&' || c == '*' || c == '{' || c == '}' || c == '\\' || c == ':' || c == '<' || c == '>' || c == '?' || c == '/' || c == '|' || c == '"' || c == '\'')
	{
		return (1);
	}
	return (0);
}
