#include "minishell.h"

/*
** ft_parse takes line as input, cycles through it iterating on "i" and subsitutes every token with its effect
*/

void	ft_parse(char **line)
{
	int i;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\'')
			i = ft_check_for_single_quotes(line, i);
		else if ((*line)[i] == '\"')
			i = ft_check_for_double_quotes(line, i);
		else if ((*line)[i] == '<' || (*line)[i] == '>')
			i = ft_check_for_redir(line, i);
		// else if ((*line)[i] == '$')
		// 	i = ft_check_for_variables(line, i);
		// else if ((*line)[i] == '|')
		// 	i = ft_check_for_pipes(line, i);
		i++;
	}
}

/*
**  "ft_get_command" takes line as input, cuts the first word out of it and gives it back as output
*/

char	*ft_get_command(char **line)
{
	char	*command;
	char	*tmp;
	int		i;

	i = 0;
	command = ft_get_name(*line, &i);
	tmp = ft_substr(*line, i, ft_strlen(*line));
	if (!tmp)
	{
		//TODO error: allocation failed
		printf("allocazione fallita\n");
		return (0);
	}
	free(*line);
	*line = tmp;
	return (command);
}

void	ft_parse_and_execute(char *line)
{
	char	*command;

	if (line && *line)
	{
		command = ft_get_command(&line);
		if (command)
		{
			printf("il comando é: %s\n", command);
		}
		// ft_check_command(command); 				//TODO vedo se esiste il comando
		ft_parse(&line);						//TODO parsing di <, >, >>, <<
		printf("la linea rimanente dopo il parsing é:%s\n\n", line);
	}
	
}
