/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 14:18:42 by mel-hiak          #+#    #+#             */
/*   Updated: 2024/08/29 14:23:55 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_env	*new_node(char *value, char *name)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (env == NULL)
		return (NULL);
	if (!name)
	{
		free(env);
		return (NULL);
	}
	env->name = name;
	env->value = value;
	env->next = NULL;
	return (env);
}

void	check_the_value(char *variable_with_content, int len, \
							int *len2, t_env *env)
{
	int	j;

	j = 0;
	while (variable_with_content[j] != '=' && variable_with_content[j])
		j++;
	if (variable_with_content[j] == '\0')
		env->value = NULL;
	else if (variable_with_content[j + 1] == '\0')
	{
		env->value = ft_strdup("");
		*len2 = len - 1;
	}
	else
	{
		env->value = ft_strdup(&variable_with_content[j] + 1);
		*len2 = len - ft_strlen(&variable_with_content[j]);
	}
}

t_env	*get_new_node(char *variable_with_content)
{
	int		len;
	int		len2;
	t_env	*env;
	t_env	*tmp;

	env = (t_env *)malloc(sizeof(t_env));
	if (env == NULL)
		return (NULL);
	len = ft_strlen(variable_with_content);
	len2 = len;
	check_the_value (variable_with_content, len, &len2, env);
	env->name = ft_substr(variable_with_content, 0, len2);
	tmp = new_node(env->value, env->name);
	if (tmp == NULL)
	{
		if (env)
		{
			free(env->name);
			free(env->value);
			free(env);
		}
		return (NULL);
	}
	free(env);
	return (tmp);
}

int	add_export_variable(t_exec *exec, int *i)
{
	t_env	*new;
	int		check;

	while (exec->cmd->args[*i])
	{
		new = get_new_node(exec->cmd->args[*i]);
		if (!new)
			return (1);
		new->check_parse = parss_export_variable(new, exec->env,*i);
		check = check_(new, new->check_parse, i);
		if (check == 2)
			return (1);
		else if (check == 1)
			continue ;
		if (find_env(exec->env, new->name))
			ft_lstremove(&(exec->env), new->name, exec);
		if (new->check_parse == 0)
			ft_env_add_back(&(exec->env), new);
		(*i)++;
	}
	return (0);
}

void	export(t_exec *exec)
{
	int	i;

	i = 1;
	exec->token = exec->token->next;
	exec->token = skip_spaces(exec->token, 1);
	if (!exec->cmd->args[i] || (exec->cmd->args[i][0] == '\0'
		&& exec->cmd->args[i + 1] == NULL && exec->token->type == ENV))
		print_export(exec);
	else
	{
		while (exec->cmd->args[i])
		{
			if (exec->cmd->args[i][0] == '\0')
			{
				check_not_valid(exec, i);
				i++;
				continue ;
			}
			if (add_export_variable(exec, &i))
				return ;
		}
	}
}
