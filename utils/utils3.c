#include "minishell.h"

char *ft_getstr_fd(int fd)
{
    char *str;
    char *tmp;
    char c[2];
    int n;

    n = read(fd, c, 1);
    if (!n)
        return (0);
    str = ft_strdup("");
    if (c[0] == '\n')
        return (str);
    c[n] = 0;
    while (n)
    {
        tmp = ft_strjoin(str, c);
        free(str);
        str = tmp;
        n = read(fd, c, 1);
        c[n] = 0;
    }
    return (str);
}
