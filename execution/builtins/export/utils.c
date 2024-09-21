/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 23:08:07 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/25 23:12:54 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	check_non_valid(t_env *new)
{
	if (new->value != NULL)
	{
		g_exit_status = 1;
		return (printf(\
			"export: '%s=%s': not a valid identifier\n", \
			new->name, new->value));
	}
	else
	{
		g_exit_status = 1;
		return (printf(\
			"export: '%s': not a valid identifier\n", new->name));
	}
}

void	check_not_valid(t_exec *exec, int i)
{
	if (exec->token->type != ENV)
	{
		printf("export: '%s': not a valid identifier\n", exec->cmd->args[i]);
		g_exit_status = 1;
	}
}

t_env	*find_env(t_env *env_list, char	*name)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
