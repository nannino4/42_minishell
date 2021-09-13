#include "minishell.h"

int ft_parse_quotes_and_variables(t_list *list_elem, int i, char **env)
{
    if ((list_elem->line)[i] == '\'')
        i = ft_parse_single_quotes(&list_elem->line, i);
    else if ((list_elem->line)[i] == '\"')
        i = ft_parse_double_quotes(&list_elem->line, i, env, WITH_VARIABLES);
    else if ((list_elem->line)[i] == '$')
        i = ft_parse_variables(&list_elem->line, i, env);
    return (i);
}

void ft_create_strings(t_list *list_elem, char **env)
{
    int i;
    int j;
    char **split;

    split = list_elem->split;
    i = -1;
    while ((list_elem->line)[++i])
    {
        if (!ft_isspace((list_elem->line)[i]))
        {
            j = i;
            while ((list_elem->line)[i] && !ft_isspace((list_elem->line)[i]))
            {
                if ((list_elem->line)[i] == '\'' || (list_elem->line)[i] == '\"' || (list_elem->line)[i] == '$')
                    i = ft_parse_quotes_and_variables(list_elem, i, env);
                i++;
            }
            *split = ft_substr(list_elem->line, j, i - j);
            if (!(*split))
            {
                //TODO error: split allocation failed
            }
            split++;
        }
    }
}

int ft_count_strings(char *line)
{
    int strings;

    strings = 0;
    while (line && *line)
    {
        if (!ft_isspace(*line))
        {
            while (*line && !ft_isspace(*line))
                line++;
            strings++;
            line--;
        }
        line++;
    }
    return (strings);
}

void ft_split_command_argv(t_list *list_elem, char **env)
{
    int strings;

    strings = ft_count_strings(list_elem->line);
    if (strings == 0)
    {
        list_elem->split = 0;
        return;
    }
    list_elem->split = malloc((strings + 1) * sizeof(char *));
    if (!list_elem->split)
    {
        //TODO error: malloc failed
    }
    (list_elem->split)[strings] = 0;
    ft_create_strings(list_elem, env);
}

int ft_final_parse(t_data *data)
{
    t_list *head;

    head = data->list;
    while (head)
    {
        ft_split_command_argv(head, data->env);
        head = head->next;
    }
    return (0);
}
