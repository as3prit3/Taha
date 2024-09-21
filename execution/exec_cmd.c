/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:05:46 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/30 21:22:02 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_cmd(t_exec *exec, char *path, t_data *data)
{
	char	*cmd;

	cmd = NULL;
	if (ft_strchr(exec->cmd->args[exec->i], '/'))
		check_access(data, exec);
	cmd = get_command(exec, path);
	if (!cmd)
	{
		cleanup(data, exec);
		exit(127);
	}
	check_if_dir(exec, data);
	if (exec->token && exec->token->type == ENV)
		execve(cmd, exec->str, exec->n_env);
	else
		execve(cmd, &exec->cmd->args[exec->i], exec->n_env);
	ft_putendl_fd("minishell: command not found", 2);
	cleanup(data, exec);
	exit(127);
}

static void	middle_cmd(t_exec *exec)
{
	close(exec->tube[2 * exec->id - 1]);
	close(exec->tube[2 * exec->id]);
	if (exec->cmd->in_file != 0)
		dup2(exec->cmd->in_file, 0);
	else
		dup2(exec->tube[2 * exec->id - 2], 0);
	if (exec->cmd->out_file != 1)
		dup2(exec->cmd->out_file, 1);
	else
		dup2(exec->tube[2 * exec->id + 1], 1);
}

static void	handle_pipe_ends(t_exec *exec)
{
	if (exec->id == 0)
	{
		dup2(exec->cmd->in_file, 0);
		close(exec->tube[0]);
		if (exec->cmd->out_file != 1)
			dup2(exec->cmd->out_file, 1);
		else
			dup2(exec->tube[1], 1);
	}
	else if (exec->id == exec->size - 1)
	{
		close(exec->tube[2 * exec->id - 1]);
		dup2(exec->cmd->out_file, 1);
		if (exec->cmd->in_file != 0)
			dup2(exec->cmd->in_file, 0);
		else
			dup2(exec->tube[2 * exec->id - 2], 0);
	}
	else
		middle_cmd(exec);
	close_right_ends(exec);
}

static void	finalize_execution(t_exec *exec, int i)
{
	if (exec->id == exec->size - 1)
	{
		close_pipes(exec);
		wait_procces(exec->fork);
	}
	if (i == 1)
		g_exit_status = 0;
	if (exec->cmd->in_file == -1 || exec->cmd->out_file == -1)
		g_exit_status = 1;
}

void	execute_cmds(t_exec *exec, t_data *data)
{
	int	i;

	if (exec->cmd->out_file == 1 && exec->id != exec->size - 1)
		exec->cmd->out_file = exec->tube[2 * exec->id + 1];
	i = builtins(exec, data);
	if (i == 0)
	{
		signal(SIGINT, SIG_IGN);
		exec->fork = fork();
		if (exec->fork == -1)
			ft_error("fork failed\n");
		else if (exec->fork == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (exec->cmd->in_file == -1 || exec->cmd->out_file == -1)
			{
				cleanup(data, exec);
				exit(1);
			}
			handle_pipe_ends(exec);
			exec_cmd(exec, get_path(exec->env), data);
		}
	}
	finalize_execution(exec, i);
}
