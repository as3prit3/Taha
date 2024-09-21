/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:14:20 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/29 15:30:03 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int		g_exit_status = 0;

bool	ft_readline(char **line, t_data *data, t_exec *exec)
{
	*line = readline("[minishell]~>");
	if (!*line || ft_strcmp(*line, "exit") == 0)
	{
		printf("exit\n");
		free(*line);
		ft_free_env(&data->envp);
		ft_free2d(exec->n_env);
		ft_cmd_clear(&data->cmd);
		ft_lstclear(&data->here_doc_name, free);
		exit(g_exit_status);
	}
	if (ft_isspace(*line))
	{
		free(*line);
		return (1);
	}
	if (ft_strlen(*line) > 0)
		add_history(*line);
	return (0);
}

void	exc_sig(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	g_exit_status = 130;
}

void	init_vars(t_data *data, t_exec *exec, char **env)
{
	*data = (t_data){0};
	*exec = (t_exec){0};
	data->in = 0;
	data->out = 1;
	create_env(exec, env);
	data->envp = exec->env;
	data->env_tab = exec->n_env;
}

int	main(int __attribute__((unused))ac, char __attribute__((unused))**av, \
char **env)
{
	char	*line;
	t_data	data;
	t_exec	exec;

	init_vars(&data, &exec, env);
	signal(SIGQUIT, SIG_IGN);
	while (42)
	{
		signal(SIGINT, exc_sig);
		data.error = 0;
		if (ft_readline(&line, &data, &exec))
			continue ;
		data.tokens = lexer(line);
		exec.token = data.tokens;
		if (!check_syntax(data.tokens))
		{
			parse(&data, data.tokens);
			if (data.error == 0)
				execute(&data, &exec);
		}
		ft_cmd_clear(&data.cmd);
		free_list(data.tokens);
		unlink_here_doc_name(data.here_doc_name);
	}
}
