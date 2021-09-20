#include "minishell.h"

void ft_close_fd(t_list *list)
{
    if (list->fd_in != -1)
        close(list->fd_in);
    list->fd_in = -1;
    if (list->fd_out != -1)
        close(list->fd_out);
    list->fd_out = -1;
}

void ft_free_list(t_list *list)
{
    char *tmp_line;
    t_list *tmp_list;
    char **tmp_split;

    while (list)
    {
        ft_close_fd(list);
        tmp_split = list->split;
        if (tmp_split)
        {
            while (*(list->split))
            {
                tmp_line = *(list->split);
                (list->split)++;
                free(tmp_line);
            }
            free(tmp_split);
        }
        if (list->line)
            free(list->line);
        tmp_list = list;
        list = list->next;
        free(tmp_list);
    }
}

void ft_free_arr(char **arr)
{
    char **tmp;

    tmp = arr;
    while (arr && *arr)
    {
        free(*arr);
        arr++;
    }
    if (tmp)
        free(tmp);
}

void ft_free_data(t_data data)
{
    if (data.line)
        free(data.line);
    ft_free_arr(data.env);
    ft_free_list(data.list);
    free(data.status_var);
}
