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

char	*ft_get_command(char **line)
{
	char	*command;
	char	*tmp;
	int		i;
	int		j;

	command = 0;
	i = 0;
	skip_spaces(line); 							//TODO salta gli spazi
	while (*line[i] && *line[i] != ' ')
		i++;
	j = 0;
	command = malloc(sizeof(char) * (i + 1));
	command[i] = 0;
	while (j < i)
	{
		command[j] = *line[j];
		j++;
	}
	tmp = ft_substr(*line, i, ft_strlen(*line));
	free(*line);
	*line = tmp;
	return (command);
}

static void	ft_parse_and_execute(char *line)
{
	char	*command;

	if (line && *line)
	{
		command = ft_get_command(&line);
		ft_check_command(command); 				//TODO vedo se esiste il comando
		ft_parse_redirections(&line);			//TODO parsing di <, >, >>, <<
	}
}

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
