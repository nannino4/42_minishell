#include "minishell.h"

int	ft_parse_quotes_and_variables(t_list *list_elem, int i, t_data *data)
{
	if ((list_elem->line)[i] == '\'')
		i = ft_parse_single_quotes(&list_elem->line, i);
	else if ((list_elem->line)[i] == '\"')
		i = ft_parse_double_quotes(&list_elem->line, i, data, WITH_VARIABLES);
	else if ((list_elem->line)[i] == '$')
		i = ft_parse_variables(&list_elem->line, i, data->env, \
				data->status_var);
	return (i);
}

int	ft_create_strings(t_list *list_elem, t_data *data)
{
	int		i;
	int		j;
	char	**split;

	split = list_elem->split;
	i = -1;
	while ((list_elem->line)[++i])
	{
		if (!ft_isspace((list_elem->line)[i]))
		{
			j = i;
			while ((list_elem->line)[i] && !ft_isspace((list_elem->line)[i]))
			{
				i = ft_parse_quotes_and_variables(list_elem, i, data);
				i++;
			}
			*split = ft_substr(list_elem->line, j, i - j);
			if (!(*split))
				return (ft_error(-1, "parse failed: allocation failed"));
			split++;
			i--;
		}
	}
	*split = 0;
	return (0);
}

int	ft_count_strings(char *line)
{
	int		strings;
	int		i;

	strings = 0;
	i = 0;
	while (line && line[i])
	{
		if (!ft_isspace(line[i]))
		{
			while (line[i] && !ft_isspace(line[i]))
			{
				i = ft_skip_quotes(line, i);
				i++;
			}
			strings++;
			i--;
		}
		i++;
	}
	return (strings);
}

int	ft_split_command_argv(t_list *list_elem, t_data *data)
{
	int		strings;

	strings = ft_count_strings(list_elem->line);
	if (strings == 0)
	{
		list_elem->split = 0;
		return (0);
	}
	list_elem->split = malloc((strings + 1) * sizeof(char *));
	if (!list_elem->split)
		return (ft_error(-1, "parse failed: allocation failed"));
	(list_elem->split)[strings] = 0;
	return (ft_create_strings(list_elem, data));
}

int	ft_final_parse(t_data *data)
{
	t_list	*head;

	head = data->list;
	while (head)
	{
		if (ft_split_command_argv(head, data))
			return (-1);
		head = head->next;
	}
	return (0);
}
