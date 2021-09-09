#include "minishell.h"

/*
** ft_parse takes line as input, cycles through it iterating on "i" and subsitutes every token with its effect
*/

void	ft_parse(t_data *data)
{
	int i;

	i = 0;
	while ((data->line)[i])
	{
		if ((data->line)[i] == '\'')
			i = ft_check_for_single_quotes(&data->line, i);
		else if ((data->line)[i] == '\"')
			i = ft_check_for_double_quotes(&data->line, i, data->env);
		else if ((data->line)[i] == '<' || (data->line)[i] == '>')
			i = ft_check_for_redir(&data->line, i, data->env);
		else if ((data->line)[i] == '$')
		 	i = ft_check_for_variables(&data->line, i, data->env);
		// else if ((data->line)[i] == '|')
		// 	i = ft_check_for_pipes(&data->line, i);
		i++;
	}
}

/*
** ft_get_name takes line as input, and gives back the first word before spaces or tokens, setting "i" at the end 
*/

// int ft_check_command(char *command, char **env)
// {
	
// }

/*
** ft_get_name takes line as input, and gives back the first word before spaces or tokens, setting "i" at the end 
*/

char	*ft_get_name(char **line, int *i, char **env, int flag)
{
	int	start;

	*i = ft_skip_spaces(*line, *i);
	start = *i;
	while ((*line)[*i] && !ft_istoken((*line)[*i]) && (*line)[*i] != ' ')
	{
		if ((*line)[*i] == '\'')
			*i = ft_check_for_single_quotes(line, *i);
		else if ((*line)[*i] == '\"')
			*i = ft_check_for_double_quotes(line, *i, env, flag);
		else if (flag && (*line)[*i] == '$')
			*i = ft_check_for_variables(line, *i, env);
		(*i)++;
	}
	return (ft_substr(*line, start, *i - start));
}

/*
**  "ft_get_command" takes line as input, cuts the first word out of it and gives it back as output
*/

char	*ft_get_command(char **line, char **env)
{
	char	*command;
	char	*tmp;
	int		i;

	i = 0;
	command = ft_get_name(line, &i, env, WITH_VARIABLES);
	tmp = ft_substr(*line, i, ft_strlen(*line));
	if (!tmp)
	{
		//TODO error: allocation failed
	}
	free(*line);
	*line = tmp;
	return (command);
}

void	ft_parse_and_execute(t_data *data)
{
	char	*command;

	if (data->line && *data->line)
	{
		command = ft_get_command(&data->line, data->env);
		printf("command:%s\n", command);
		// ft_check_command(command, data->env);
		ft_parse(data);
		printf("remaining line:%s\n", data->line);
	}
}
