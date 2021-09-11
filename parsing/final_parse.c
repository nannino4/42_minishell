#include "minishell.h"

int ft_copy_string(t_list *list_elem, int i)
{
    while ((list_elem->line)[j] && (list_elem->line)[j] != ' ')
    {
        if ((list_elem->line)[i] == '\'')
            ft_split_single_quotes(list_elem, i);
        else if ((list_elem->line)[i] == '\"')
            ft_split_double_quotes(list_elem, i);
        j++;
    }
}

void ft_create_strings(t_list *list_elem)
{
    int i;
    int j;
    char **split;

    split = list_elem->split;
    i = 0;
    while ((list_elem->line)[i])
    {
        if (!ft_isspace((list_elem->line)[i]))
        {
            j = i;
            i = ft_copy_string(list_elem, i);
            *split = ft_substr(list_elem->line, j, i - j);
            (*split)++;
        }
        i++;
    }
}

int ft_count_strings(char *line)
{
    int strings;

    //TODO
    return (strings);
}

void ft_split_command_argv(t_list *list_elem)
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
    ft_create_strings(list_elem);
}

int ft_final_parse(t_data *data)
{
    t_list *head;

    head = data->list;
    while (head)
    {
        ft_split_command_argv(head);
        head = head->next;
    }
    return (0);
}
