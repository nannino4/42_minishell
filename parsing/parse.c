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

char *ft_get_name(char **line, int *i, char **env, int flag)
{
	int start;

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

void ft_parse(t_data *data)
{
	int i;

	if ((data->line)[i] == '|')
		i = ft_check_for_pipes(&data->line, i);
	i = 0;
	while ((data->line)[i])
	{
		if ((data->line)[i] == '\'')
			i = ft_check_for_single_quotes(&data->line, i);
		else if ((data->line)[i] == '\"')
			i = ft_check_for_double_quotes(&data->line, i, data->env, WITH_VARIABLES);
		else if ((data->line)[i] == '<' || (data->line)[i] == '>')
			i = ft_check_for_redir(&data->line, i, data->env);
		else if ((data->line)[i] == '$')
			i = ft_check_for_variables(&data->line, i, data->env);
		i++;
	}
}

void ft_cut_pipe(t_data *data, int i)
{
	t_list *elem;

	elem = malloc(sizeof(t_list));
	elem->line = ft_substr(data->line, 0, i);
	ft_add_elem(data->list, elem);
	while (*(data->line) != '|')
	{
		(data->line)++;
	}
	(data->line)++;
}

int ft_parse_pipes(t_data *data)
{
	int word_flag;
	int i;

	word_flag = 0;
	i = 0;
	while ((data->line)[i])
	{
		if ((data->line)[i] == '|')
		{
			if (!word_flag)
			{
				// TODO error: unexpected '|'
			}
			return (1); //error management
			word_flag = 0;
			ft_cut_pipe(data, i);
			i = -1;
		}
		else if (!ft_isspace((data->line)[i]))
			word_flag = 1;
		i++;
	}
	if (!word_flag)
	{
		// TODO error: line ending with unexpected '|'
	}
	ft_cut_pipe(data, i);
}

void ft_parse_and_execute(t_data data)
{
	if (*(data.line))
	{
		if (ft_parse_pipes(&data))
		{
			//TODO error: pipes error
		}
		// ft_parse_ioredir(&data);							TODO
		// ft_parse_split(&data);							TODO
		// ft_check_commands(command, data->env);
	}
}
