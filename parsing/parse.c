#include "minishell.h"

void	ft_parse(char **line)
{
	int i;

	i = 0;
	while (*line[i])
	{
		if (*line[i] == '\'')
			i = ft_check_for_single_quotes(line, i);
		else if (*line[i] == '\"')
			i = ft_check_for_double_quotes(line, i);
		else if (*line[i] == '<' || *line[i] == '>')
			i = ft_check_for_redirections(line, i);
		else if (*line[i] == '$')
			i = ft_check_for_variables(line, i);
		else if (*line[i] == '|')
			i = ft_check_for_pipes(line, i);
		i++;
	}
}

char	*ft_get_command(char **line)
{
	char	*command;
	char	*tmp;
	int		i;
	int		j;

	command = 0;
	i = 0;
	skip_spaces(line); 							//TODO salta gli spazi
	while (*line[i] && *line[i] != ' ')
		i++;
	j = 0;
	command = malloc(sizeof(char) * (i + 1));
	command[i] = 0;
	while (j < i)
	{
		command[j] = *line[j];
		j++;
	}
	tmp = ft_substr(*line, i, ft_strlen(*line));
	if (!tmp)
	{
		//TODO error: allocation failed
	}
	free(*line);
	*line = tmp;
	return (command);
}

static void	ft_parse_and_execute(char *line)
{
	char	*command;

	if (line && *line)
	{
		command = ft_get_command(&line);
		ft_check_command(command); 				//TODO vedo se esiste il comando
		ft_parse(&line);						//TODO parsing di <, >, >>, <<
	}
}
