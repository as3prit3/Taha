/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:18:38 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/29 17:45:36 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_cmd(t_data *data, t_compo **token, char *str, enum e_type type)
{
	char	*tmp;
	char	*cmd;

	if (*token)
		*token = skip_spaces(*token, 1);
	while (*token && !ft_space((*token)->type) && (*token)->type != PIPE)
	{
		if (is_redir(type) && (*token)->type == ENV)
		{
			if (data->expend)
				free(data->expend);
			data->expend = ft_strdup((*token)->content);
		}
		cmd = parse_cmd(data, token);
		tmp = str;
		str = ft_strjoin(tmp, cmd);
		free(tmp);
		if (*token && (*token)->type != ENV && (*token)->type != EX_STATUS)
			free(cmd);
		if (str && *token && (*token)->next && is_redir((*token)->next->type))
			break ;
		if (*token)
			*token = (*token)->next;
	}
	return (str);
}

void	get_redir(t_data *data, t_compo **token, enum e_type type, char *str)
{
	if (str)
		ft_lstadd_back(&data->lst_cmd, ft_lstnew(str));
	str = ft_strdup("");
	*token = (*token)->next;
	if (type == HERE_DOC && data->error != 1)
		child_here_doc(data, token, &str);
	else
	{
		str = get_cmd(data, token, str, type);
		if (type == REDIR_IN)
			in_file(data, str);
		else if (type == REDIR_OUT)
			out_file(data, str);
		else if (type == APPEND)
			append(data, str);
	}
	free(str);
}

void	handel_cmd(t_data *data, t_compo **token)
{
	char	*str;

	str = NULL;
	while (*token && !((*token)->type == PIPE && (*token)->state == GENERAL))
	{
		if (is_redir((*token)->type))
			get_redir(data, token, (*token)->type, str);
		else
		{
			if (!str && !ft_space((*token)->type))
				str = ft_strdup("");
			if (!ft_space((*token)->type) && (*token)->state == GENERAL)
				str = get_cmd(data, token, str, WORD);
			if (((str) && (!*token || ft_space((*token)->type)))
				|| (*token && (*token)->type == PIPE))
			{
				add_token_to_list(data, str);
				str = NULL;
			}
		}
		if (*token && (*token)->type == PIPE)
			break ;
		if (*token)
			*token = (*token)->next;
	}
}

void	parse(t_data *data, t_compo *token)
{
	token = skip_spaces(token, 1);
	while (token)
	{
		handel_cmd(data, &token);
		if (!token || token->type == PIPE)
			create_cmd(data);
		if (token)
			token = token->next;
	}
	print_redir_error(data->lst_err, data);
	ft_lstclear(&data->lst_err, free);
}
