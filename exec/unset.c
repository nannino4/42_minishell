#include "minishell.h"

static int ft_is_var_valid(char *var)
{
    int i;

    i = 0;
    if (!ft_isalpha(var[i]) && var[i] != '_')
        return (0);
    while (var[i] && var[i] != '=')
    {
        if (var[i] != '_' && !ft_isalnum(var[i]))
            return (0);
        i++;
    }
    return (1);
}

void ft_remove_var(char *var, int len, t_data *data)
{
    char **new_env;
    int strings;
    int i;
    int j;

    strings = ft_arrlen(data->env) - 1;
    new_env = malloc((strings + 1) * sizeof(void *));
    if (!new_env)
    {
        // TODO error management: allocation failed
    }
    new_env[strings] = 0;
    i = 0;
    j = 0;
    while (i < strings - 1)
    {
        if (data->env[i] + len + 1 != ft_getenv(var, data->env))
            new_env[i++] = ft_strdup(data->env[j]);
        j++;
    }
    ft_free_arr(data->env);
    data->env = new_env;
}

void ft_unset(t_data *data)
{
    int i;
    int ret;

    ret = 0;
    i = 1;
    while (data->list->split[i])
    {
        if (ft_is_var_valid(data->list->split[i]))
        {
            if (ft_getenv(data->list->split[i], data->env))
                ft_remove_var(data->list->split[i], ft_strlen(data->list->split[i]), data);
        }
        else
            ret = 1;
        i++;
    }
    exit(ret);
}
