/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfabi <jfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:19:14 by jfabi             #+#    #+#             */
/*   Updated: 2021/06/17 15:04:51 by jfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    char *line;

    line = readline("# Orders, my Lord? ");
    if (line && ft_strlen(line) > 0)
        add_history(line);
    while (line)
    {
        ft_parse_and_execute(line);
        // execute(line);
        line = readline("# Orders, my Lord? ");
        if (line && ft_strlen(line) > 0)
            add_history(line);
    }
    printf("exit\n");
}
