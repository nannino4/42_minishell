#include "minishell.h"

void ft_input_redir(char **line, int i, char **env)
{
	int file;
	int j;
	int diff;
	char *name;

	j = i;
	i++;
	name = ft_get_name(line, &i, env, WITH_VARIABLES);
	if (!name || !*name)
	{
		//TODO error management: nome file invalido
	}
	file = open(name, O_RDONLY);
	if (file == -1)
	{
		//TODO error: file openining
	}
	if (dup2(file, STDIN_FILENO) == -1)
	{
		//TODO error: dup2 failed
	}
	close(file);
	diff = i - j;
	ft_cut_line_io_redir(line, i, j);
}

void ft_output_redir(char **line, int i, char **env)
{
	int file;
	char *name;
	int j;

	j = i;
	i++;
	name = ft_get_name(line, &i, env, WITH_VARIABLES);
	if (!name || !*name)
	{
		//TODO error management: nome file invalido
	}
	file = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
	{
		//TODO error: file openining
	}
	if (dup2(file, STDOUT_FILENO) == -1)
	{
		//TODO error: dup2 failed
	}
	close(file);
	ft_cut_line_io_redir(line, i, j);
}

void ft_double_output_redir(char **line, int i, char **env)
{
	int file;
	int j;
	int diff;
	char *name;

	j = i;
	i += 2;
	name = ft_get_name(line, &i, env, WITH_VARIABLES);
	if (!name || !*name)
	{
		//TODO error management: nome file invalido
	}
	file = open(name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (file == -1)
	{
		//TODO error: file can't be opened
	}
	if (dup2(file, STDOUT_FILENO) == -1)
	{
		//TODO error: dup2 failed
	}
	close(file);
	diff = i - j;
	ft_cut_line_io_redir(line, i, j);
}

void ft_readline(char *end_word, int *fd)
{
	char *tmp;
	char *buffer;

	buffer = readline(">");
	while (buffer && !(!ft_strncmp(buffer, end_word, ft_strlen(buffer)) && ft_strlen(buffer) == ft_strlen(end_word)))
	{
		tmp = ft_strjoin(buffer, "\n");
		free(buffer);
		buffer = tmp;
		ft_putstr_fd(buffer, fd[1]);
		free(buffer);
		buffer = readline(">");
	}
	if (buffer)
		free(buffer);
}

void ft_double_input_redir(char **line, int i)
{
	char *end_word;
	int j;
	int fd[2];

	if (pipe(fd))
	{
		//TODO error: pipe failed
	}
	j = i;
	i += 2;
	end_word = ft_get_name(line, &i, 0, NO_VARIABLES);
	ft_readline(end_word, fd);
	free(end_word);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		//TODO error: dup2 failed
	}
	close(fd[0]);
	ft_cut_line_io_redir(line, i, j);
}

int ft_check_for_redir(char **line, int i, char **env)
{
	if ((*line)[i] == '>' && (*line)[i + 1] == '>')
		ft_double_output_redir(line, i, env);
	else if ((*line)[i] == '<' && (*line)[i + 1] == '<')
		ft_double_input_redir(line, i);
	else if ((*line)[i] == '<')
		ft_input_redir(line, i, env);
	else if ((*line)[i] == '>')
		ft_output_redir(line, i, env);
	return (i); //TODO controlla output i
}
