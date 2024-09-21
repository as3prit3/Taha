/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:15:04 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/30 10:14:27 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	unlink_here_doc_name(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp)
	{
		unlink(tmp->content);
		tmp = tmp->next;
	}
}

void	wait_procces(int pid)
{
	int	status;
	int	id;

	while (1)
	{
		id = wait(&status);
		if (id == -1)
			break ;
		if (id == pid)
			g_exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status) && id == pid)
		{
			if (WTERMSIG(status) == SIGINT)
			{
				g_exit_status = 130;
				ft_putstr_fd("\n", 2);
			}
			if (WTERMSIG(status) == SIGQUIT)
			{
				ft_putstr_fd("Quit (core dumped)\n", 2);
				g_exit_status = 131;
			}
		}
	}
}

void	create_pipes(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->size - 1)
	{
		if (pipe(&(exec->tube[2 * i])) < 0)
			ft_error("pipe failed\n");
		i++;
	}
}
