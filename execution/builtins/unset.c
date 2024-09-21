/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:46:03 by mel-hiak          #+#    #+#             */
/*   Updated: 2024/08/27 14:58:42 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lstremove(t_env **begin_list, void *data_ref, t_exec *exec)
{
	t_env	*curr;

	if (*begin_list == NULL || begin_list == NULL)
		return ;
	curr = *begin_list;
	if (ft_strcmp(curr->name, data_ref) == 0)
	{
		*begin_list = curr->next;
		free(curr->name);
		free(curr->value);
		free(curr);
		ft_lstremove(begin_list, data_ref, exec);
	}
	else
		ft_lstremove(&curr->next, data_ref, exec);
}

void	unset(t_exec *exec)
{
	int		i;

	i = 1;
	while (exec->cmd->args[i])
	{
		ft_lstremove(&(exec->env), exec->cmd->args[i], exec);
		i++;
	}
}
