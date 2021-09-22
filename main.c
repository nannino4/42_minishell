#include "minishell.h"

void	sigint_handler(int sig)
{
	pid_t	pid;
	int		status;

	sig = 0;
	pid = waitpid(-1, &status, WNOHANG);
	if (pid == -1)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \n", 1);
		rl_on_new_line();
		ft_putstr_fd(BHBLU"––––––––––––\n"RESET, 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	ft_parse_and_execute(t_data *data)
{
	int		ret;

	ret = ft_parse_pipes(data);
	if (ret)
		return (ret);
	ret = ft_parse_ioredir(data);
	if (ret)
		return (ret);
	ret = ft_final_parse(data);
	if (ret)
		return (ret);
	return (ft_exec(data));
}

void	ft_init(t_data *data, char **envp)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	ft_env_creation(data, envp);
	data->line = ft_strdup("");
	data->list = 0;
	data->status_var = ft_strdup("0");
	data->exit_flag = 0;
}

void	ft_main_utility(t_data *data)
{
	char	*tmp;

	add_history(data->line);
	tmp = ft_itoa(ft_parse_and_execute(data));
	free(data->status_var);
	data->status_var = tmp;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		status;

	if (argc > 1 && argv)
		ft_error_exit(127, "./minishell: too many arguments");
	ft_init(&data, envp);
	while (data.line && !data.exit_flag)
	{
		ft_free_list(&data);
		free(data.line);
		printf(BHBLU"––––––––––––\n"RESET);
		data.line = readline("# ORDERS, MY LORD >: ");
		if (data.line && *(data.line))
			ft_main_utility(&data);
	}
	printf("exit\n");
	status = ft_atoi(data.status_var);
	ft_free_data(&data);
	exit(status);
}
