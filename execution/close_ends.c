/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_ends.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:07:51 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/19 15:08:27 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_right_ends(t_exec *exec)
{
	int	i;

	i = -1;
	while (++i < exec->nb_pipe)
		if (i != 2 * exec->id && i != 2 * exec->id + 1)
			close(exec->tube[i]);
}

void	close_pipes(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->nb_pipe)
		close(exec->tube[i++]);
}

void	ft_close(t_cmd *val)
{
	t_cmd	*tmp;

	tmp = val;
	while (tmp)
	{
		if (tmp->in_file > 2)
			close(tmp->in_file);
		if (tmp->out_file > 2)
			close(tmp->out_file);
		tmp = tmp->next;
	}
}
