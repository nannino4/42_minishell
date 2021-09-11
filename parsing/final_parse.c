#include "minishell.h"

void ft_create_strings(t_list *list_elem)
{
    int i;
    int j;
    char **split;

    split = list_elem->split;
    i = 0;
    while ((list_elem->line)[i])
    {
        i = ft_skip_spaces(list_elem->line, i);
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
        return ;
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
