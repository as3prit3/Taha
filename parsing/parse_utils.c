/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:25:22 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/29 17:43:15 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*parse_word(t_compo **token)
{
	char	*str;

	str = ft_strdup((*token)->content);
	return (str);
}

static int	change_content(t_env *env, char *tmp, t_compo **token)
{
	if (ft_strcmp(env->name, tmp + 1) == 0)
	{
		free((*token)->content);
		(*token)->content = ft_strdup(env->value);
		return (1);
	}
	return (0);
}

char	*parse_env(t_data *data, t_compo **token)
{
	char	*tmp;
	t_env	*env;

	tmp = ft_strdup((*token)->content);
	env = data->envp;
	if ((*token)->type == EX_STATUS)
	{
		free((*token)->content);
		(*token)->content = ft_itoa(g_exit_status);
	}
	else
	{
		data->exp_status = 1;
		while (env)
		{
			if (change_content(env, tmp, token))
				break ;
			env = env->next;
		}
		modify_token_content(token, tmp, env);
	}
	return (free(tmp), (*token)->content);
}

char	*parse_quote(t_data *data, t_compo **tok, enum e_type type)
{
	char	*str;
	char	*tmp;

	str = NULL;
	*tok = (*tok)->next;
	while (*tok)
	{
		if (!str)
			str = ft_strdup("");
		if ((*tok)->type != type)
		{
			if ((*tok)->type == ENV || (*tok)->type == EX_STATUS)
				parse_env(data, tok);
			tmp = str;
			str = ft_strjoin(tmp, (*tok)->content);
			free(tmp);
		}
		else
			break ;
		if (*tok)
			*tok = (*tok)->next;
	}
	return (str);
}

char	*parse_cmd(t_data *data, t_compo **token)
{
	char	*cmd;

	cmd = NULL;
	if (*token)
	{
		if (*token && (*token)->type == WORD)
			cmd = parse_word(token);
		if (*token && ((*token)->type == SQUOTE || (*token)->type == DQUOTE))
			cmd = parse_quote(data, token, (*token)->type);
		if (*token && ((*token)->type == ENV || (*token)->type == EX_STATUS))
			cmd = parse_env(data, token);
	}
	return (cmd);
}
