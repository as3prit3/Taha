/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:59:44 by mel-hiak          #+#    #+#             */
/*   Updated: 2024/08/27 17:15:03 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	check_(t_env *new, int check_parse, int *i)
{
	if (check_parse)
	{
		if (check_parse == -1 && *i == 1)
		{
			ft_free_env(&new);
			return (2);
		}
		(*i) += 1;
		ft_free_env(&new);
		return (1);
	}
	return (0);
}

void	ft_swaped(t_env *a, t_env *b)
{
	char	*tmp_name;
	char	*tmp_value;

	tmp_name = a->name;
	tmp_value = a->value;
	a->name = b->name;
	a->value = b->value;
	b->name = tmp_name;
	b->value = tmp_value;
}

void	ft_list_sort(t_env **env)
{
	t_env	*tmp;
	int		i;

	if (!env || !*env)
		return ;
	i = 1;
	while (i)
	{
		i = 0;
		tmp = *env;
		while (tmp->next)
		{
			if (ft_strcmp(tmp->name, tmp->next->name) > 0)
			{
				ft_swaped(tmp, tmp->next);
				i = 1;
			}
			tmp = tmp->next;
		}
	}
}

void	print_export(t_exec *exec)
{
	t_env	*tmp;

	tmp = exec->env;
	ft_list_sort(&tmp);
	while (tmp)
	{
		if (tmp->value)
		{
			ft_putstr_fd("declare -x ", exec->cmd->out_file);
			ft_putstr_fd(tmp->name, exec->cmd->out_file);
			ft_putstr_fd("=\"", exec->cmd->out_file);
			ft_putstr_fd(tmp->value, exec->cmd->out_file);
			ft_putstr_fd("\"\n", exec->cmd->out_file);
		}
		else if (!tmp->value)
		{
			ft_putstr_fd("declare -x ", exec->cmd->out_file);
			ft_putstr_fd(tmp->name, exec->cmd->out_file);
			ft_putstr_fd("\n", exec->cmd->out_file);
		}
		tmp = tmp->next;
	}
}

void	*concatenat_variable(t_env *new, t_env *env_list)
{
	t_env	*tmp;
	char	*tmp_name;
	char	*tmp_value;

	if (!new || !new->name || !new->value)
		return (NULL);
	tmp_name = ft_strtrim(new->name, "+");
	if (!tmp_name)
		return (NULL);
	free (new->name);
	new->name = tmp_name;
	tmp = find_env(env_list, new->name);
	if (tmp && tmp->value && new->value[0] != '\0')
	{
		tmp_value = ft_strjoin(tmp->value, new->value);
		if (!tmp_value)
			return (NULL);
		free(new->value);
		new->value = tmp_value;
	}
	return (NULL);
}
