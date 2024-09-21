/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:09:59 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/25 10:57:02 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_error(char *str)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(str, 2);
	g_exit_status = 1;
	exit(g_exit_status);
}

void	exec_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	check_if_dir(t_exec *exec, t_data *data)
{
	DIR	*dir;

	dir = NULL;
	if (exec->cmd->args[exec->i] && ft_strchr(exec->cmd->args[exec->i], '/'))
		dir = opendir(exec->cmd->args[exec->i]);
	if (dir)
	{
		closedir(dir);
		ft_putstr_fd(exec->cmd->args[exec->i], 2);
		ft_putstr_fd(": is a directory\n", 2);
		cleanup(data, exec);
		exit(126);
	}
}

	/*else
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		cleanup(data, exec);
		exit(127);
	}*/