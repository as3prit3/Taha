/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 22:15:44 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/29 16:13:57 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit_error(char *str, char *error)
{
	ft_putstr_fd("minishell: exit: ", 2);
	if (str)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(error, 2);
	g_exit_status = 1;
}

void	exit_failed(t_data *data, t_exec *exec, long long nb, char *str)
{
	if (nb > 2147483647 || nb < -2147483647)
	{
		ft_exit_error(str, "numeric argument required");
		cleanup(data, exec);
		exit(2);
	}
	if (nb == -1)
	{
		cleanup(data, exec);
		exit(255);
	}
}

int	valid_args(char *str, t_data *data, t_exec *exec)
{
	long long	nb;
	int			i;

	i = 0;
	if (!str)
		return (0);
	nb = ft_atoi(str);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	exit_failed(data, exec, nb, str);
	return (1);
}

int	check_args(t_exec *exec, char *str, t_data *data)
{
	long long	nb;

	if (valid_args(str, data, exec))
	{
		if (exec->cmd->args[exec->i + 1])
			ft_exit_error("", "too many arguments");
		else
		{
			nb = ft_atoi(str);
			if (nb >= 0 && nb <= 256)
			{
				cleanup(data, exec);
				exit(nb);
			}
			else
			{
				cleanup(data, exec);
				exit(nb % 256);
			}
		}
	}
	else
		return (1);
	return (0);
}

void	ft_exit(t_exec *exec, t_data *data)
{
	char		*str;

	exec->i++;
	str = exec->cmd->args[exec->i];
	if (exec->size == 1)
	{
		ft_putstr_fd("exit\n", exec->cmd->out_file);
		if (!str)
		{
			cleanup(data, exec);
			exit(g_exit_status);
		}
		else
		{
			if (check_args(exec, str, data) == 1)
			{
				ft_exit_error(str, "numeric argument required");
				cleanup(data, exec);
				exit(2);
			}
		}
	}
}
