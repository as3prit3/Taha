/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:22:56 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/25 23:37:21 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_for_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		i += 2;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	echo(t_exec *exec)
{
	int	nl;

	nl = 0;
	exec->i++;
	if (exec->cmd->args[exec->i])
	{
		while (check_for_n(exec->cmd->args[exec->i]))
		{
			nl = 1;
			exec->i++;
		}
		while (exec->cmd->args[exec->i])
		{
			ft_putstr_fd(exec->cmd->args[exec->i], exec->cmd->out_file);
			if (exec->cmd->args[exec->i + 1])
				ft_putstr_fd(" ", exec->cmd->out_file);
			exec->i++;
		}
		if (!nl)
			ft_putstr_fd("\n", exec->cmd->out_file);
	}
	else
		ft_putstr_fd("\n", exec->cmd->out_file);
	g_exit_status = 0;
}
