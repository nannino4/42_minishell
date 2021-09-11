#include "minishell.h"

// int ft_check_command(char *command, char **env)
// {
// 	char *path;

// 	path = ft_getenv("PATH", env);
// 	if (!ft_strchr(command, '/') && path)
// 	{
// 		// TODO cerca nel path ed esegui
// 	}
// 	else
// 	{
// 	}

// char *ft_get_command(char **line, char **env)
// {
// 	char *command;
// 	char *tmp;
// 	int i;

// 	i = 0;
// 	command = ft_get_name(line, &i, env, WITH_VARIABLES);
// 	tmp = ft_substr(*line, i, ft_strlen(*line));
// 	if (!tmp)
// 	{
// 		//TODO error: allocation failed
// 	}
// 	free(*line);
// 	*line = tmp;
// 	return (command);
// }
// }

// void ft_parse(t_data *data)
// {
// 	int i;

// 	if ((data->line)[i] == '|')
// 		i = ft_check_for_pipes(&data->line, i);
// 	i = 0;
// 	while ((data->line)[i])
// 	{
// 		if ((data->line)[i] == '\'')
// 			i = ft_check_for_single_quotes(&data->line, i);
// 		else if ((data->line)[i] == '\"')
// 			i = ft_check_for_double_quotes(&data->line, i, data->env, WITH_VARIABLES);
// 		else if ((data->line)[i] == '<' || (data->line)[i] == '>')
// 			i = ft_check_for_redir(&data->line, i, data->env);
// 		else if ((data->line)[i] == '$')
// 			i = ft_check_for_variables(&data->line, i, data->env);
// 		i++;
// 	}
// }

