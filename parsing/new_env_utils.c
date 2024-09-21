/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:36:17 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/19 11:52:44 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*new_env(char *name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	add_env(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	env_len(t_env *env)
{
	int		i;

	if (!env)
		return (0);
	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void	ft_free_env(t_env **env)
{
	t_env	*tmp;
	t_env	*next;

	if (!env || !*env)
		return ;
	if (*env)
	{
		tmp = *env;
		while (tmp)
		{
			next = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			tmp = next;
		}
		*env = NULL;
	}
}
