/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 09:52:40 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/30 19:46:49 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtins(t_exec *exec, t_data *data)
{
	if (ft_strcmp(exec->cmd->args[exec->i], "cd") == 0)
	{
		exec->i++;
		return (cd(exec->cmd->args[exec->i], exec));
	}
	else if (ft_strcmp(exec->cmd->args[exec->i], "echo") == 0)
		return (echo(exec), 1);
	else if (ft_strcmp(exec->cmd->args[exec->i], "env") == 0)
		return (fenv(exec));
	else if (ft_strcmp(exec->cmd->args[exec->i], "pwd") == 0)
		return (pwd(exec), 1);
	else if (ft_strcmp(exec->cmd->args[exec->i], "unset") == 0)
		return (unset(exec), 1);
	else if (ft_strcmp(exec->cmd->args[exec->i], "export") == 0)
	{
		export(exec);
		if (g_exit_status == 1)
			return (2);
		return (1);
	}
	else if (ft_strcmp(exec->cmd->args[exec->i], "exit") == 0)
		return (ft_exit(exec, data), 2);
	return (0);
}

void	one_cmd_child(t_exec *exec, t_data *data)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (exec->cmd->in_file == -1 || exec->cmd->out_file == -1)
	{
		cleanup(data, exec);
		exit(1);
	}
	if (exec->cmd->in_file != 0)
		dup2(exec->cmd->in_file, 0);
	if (exec->cmd->out_file != 1)
		dup2(exec->cmd->out_file, 1);
	exec_cmd(exec, get_path(exec->env), data);
}

void	one_cmd(t_exec *exec, t_data *data)
{
	int	i;

	i = builtins(exec, data);
	if (exec->env)
	{
		ft_free2d(exec->n_env);
		exec->n_env = list_to_tab(&exec->env);
	}
	if (i == 0)
	{
		signal(SIGINT, SIG_IGN);
		exec->fork = fork();
		if (exec->fork == -1)
			ft_error("fork failed\n");
		else if (exec->fork == 0)
			one_cmd_child(exec, data);
		wait_procces(exec->fork);
	}
	if (i == 1)
		g_exit_status = 0;
	if (exec->cmd->in_file == -1 || exec->cmd->out_file == -1)
		g_exit_status = 1;
}

void	multi_cmd(t_exec *exec, t_data *data)
{
	t_exec	*tmp;

	tmp = exec;
	exec->nb_pipe = 2 * (exec->size - 1);
	exec->tube = malloc(sizeof(int) * exec->nb_pipe);
	if (!exec->tube)
		ft_error("malloc failed\n");
	create_pipes(exec);
	exec->id = 0;
	while (exec->id < exec->size)
	{
		execute_cmds(exec, data);
		exec->id++;
		exec->cmd = exec->cmd->next;
		exec->i = 0;
		while (exec->token && exec->token->type != ENV)
			exec->token = exec->token->next;
	}
	ft_close(tmp->cmd);
	if (tmp->tube)
	{
		free(tmp->tube);
		tmp->tube = NULL;
	}
}

void	execute(t_data *data, t_exec *exec)
{
	exec->cmd = data->cmd;
	exec->i = 0;
	exec->size = ft_cmdsize(exec->cmd);
	if (exec->size == 0)
		return ;
	while (exec->cmd->args[exec->i]
		&& ft_strcmp(exec->cmd->args[exec->i], "") == 0)
		exec->i++;
	if (!exec->cmd->args[exec->i])
	{
		g_exit_status = 0;
		return ;
	}
	if (exec->size == 1)
		one_cmd(exec, data);
	else
		multi_cmd(exec, data);
}
