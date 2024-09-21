/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:48:58 by mel-hiak          #+#    #+#             */
/*   Updated: 2024/08/28 23:29:28 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	parss_export_variable(t_env *new, t_env *env_list, int i)
{
	int		len;
	int		check_parse;

	if (!new || !new->name)
		return (-1);
	len = ft_strlen(new->name);
	check_parse = check_special_char(new, len, i);
	if (check_parse)
	{
		if (check_parse == -1)
			return (-1);
		return (1);
	}
	if (len != 0)
		if (new->name[len - 1] == '+')
			concatenat_variable(new, env_list);
	return (0);
}

void	ft_env_add_back(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

int	check_signe_plus(t_env *new)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (new->name && new->name[i])
	{
		if (new->name[i] == '+')
			j++;
		i++;
	}
	if (!ft_strcmp(new->name, "") || (new->name[i - 1] == '+' && j == 1))
		return (0);
	if (new->name && ((new->name[i - 1] == '+' && j > 1) || \
		(new->name[i - 1] == '+' && (!new->value || new->value[0] == '\0'))))
		return (1);
	else
		return (0);
}

int	check_special_char_(t_env *new, int i)
{
	if (ft_isdigit(new->name[0]) || new->name[0] == '+')
	{
		g_exit_status = 1;
		return (printf(\
			"bash: export: `%s': not a valid identifier\n", new->name));
	}
	if (new->name[0] == '-' && i == 1)
	{
		printf("bash: export: -%c: invalid option\n", new->name[0]);
		printf(\
			"export: usage: export [-fn] [name[=value] ...] or export -p\n");
		g_exit_status = 1;
		return (1);
	}
	if (check_signe_plus(new))
	{
		g_exit_status = 1;
		return (printf(\
			"bash: export: `%s': not a valid identifier\n", new->name));
	}
	return (0);
}

int	check_special_char(t_env *new, int len, int i)
{
	int	j;

	j = 0;
	if (check_special_char_(new, i))
		return (0);
	if (ft_strcmp(new->name, "") == 0)
	{
		g_exit_status = 1;
		return (printf(\
			"bash: export: `=%s': not a valid identifier\n", new->value), 0);
	}
	while (new->name[j])
	{
		if (((new->name[j] <= 64 && !ft_isdigit(new->name[j])) \
		|| (new->name[j] >= 91 && new->name[j] <= 96 && new->name[j] != '_') \
		|| new->name[j] >= 123) && new->name[len - 1] != '+')
		{
			return (check_non_valid(new));
		}
		j++;
	}
	return (0);
}
