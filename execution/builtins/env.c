/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:29:25 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/27 14:58:29 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_env(t_env *tmp, t_exec *exec)
{
	while (tmp)
	{
		if (tmp->value)
		{
			ft_putstr_fd(tmp->name, exec->cmd->out_file);
			ft_putstr_fd("=", exec->cmd->out_file);
			ft_putendl_fd(tmp->value, exec->cmd->out_file);
		}
		tmp = tmp->next;
	}
}

int	fenv(t_exec *exec)
{
	t_env	*tmp;

	tmp = exec->env;
	exec->i++;
	if (exec->cmd->args[exec->i])
	{
		ft_putstr_fd("env: ", exec->cmd->out_file);
		ft_putstr_fd(exec->cmd->args[exec->i], exec->cmd->out_file);
		ft_putstr_fd(": No such file or directory\n", exec->cmd->out_file);
		g_exit_status = 1;
		return (2);
	}
	else
	{
		print_env(tmp, exec);
		g_exit_status = 0;
	}
	return (1);
}
