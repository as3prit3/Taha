/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:42:08 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/29 17:45:28 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_token_to_list(t_data *data, char *str)
{
	if (!ft_strcmp(str, ""))
		free(str);
	else
		ft_lstadd_back(&data->lst_cmd, ft_lstnew(str));
}

void	modify_token_content(t_compo **token, char *tmp, t_env *env)
{
	if (!env && ft_strlen(tmp) != 1)
	{
		free((*token)->content);
		(*token)->content = ft_strdup("");
	}
	else if (!env && ft_strlen(tmp) == 1)
	{
		free((*token)->content);
		(*token)->content = ft_strdup(tmp);
	}
}

char	*get_name(char *str, char c)
{
	char	*new;
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	new = malloc(i + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	**list_to_tab(t_env **env)
{
	char	**tab;
	t_env	*tmp;
	int		i;
	char	*str;
	t_env	*next;

	i = env_len(*env);
	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return (NULL);
	i = 0;
	tmp = *env;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->value)
		{
			str = ft_strjoin(tmp->name, "=");
			tab[i++] = ft_strjoin(str, tmp->value);
			free(str);
		}
		tmp = next;
	}
	tab[i] = NULL;
	return (tab);
}

void	create_env(t_exec *exec, char **env)
{
	char	*name;
	char	*value;
	int		i;

	i = -1;
	exec->env = NULL;
	while (env && env[++i])
	{
		name = get_name(env[i], '=');
		value = ft_strdup(ft_strchr(env[i], '=') + 1);
		add_env(&exec->env, new_env(name, value));
	}
	exec->n_env = list_to_tab(&exec->env);
}
