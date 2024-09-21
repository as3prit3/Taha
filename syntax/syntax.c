/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:08:49 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/29 15:35:59 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	print_synth_err(char *content)
{
	ft_putstr_fd("syntax error near unexpected token ", 2);
	ft_putstr_fd(content, 2);
	ft_putstr_fd("\n", 2);
	g_exit_status = 2;
}

static bool	check_pipe_syn(t_compo *node)
{
	t_compo	*prev;
	t_compo	*next;

	prev = skip_spaces(node->prev, 0);
	next = skip_spaces(node->next, 1);
	if (!prev || !next || is_redir(prev->type) || next->type == PIPE)
	{
		print_synth_err("'|'");
		return (1);
	}
	return (false);
}

static bool	check_redir_syn(t_compo *node)
{
	t_compo	*next;

	next = skip_spaces(node->next, 1);
	if (!next)
	{
		print_synth_err("'newline'");
		return (true);
	}
	else if (is_redir(next->type))
	{
		print_synth_err(next->content);
		return (true);
	}
	return (false);
}

static bool	check_quote_syn(t_compo **node, enum e_type type)
{
	while (*node)
	{
		*node = (*node)->next;
		if (!*node || (*node)->type == type)
			break ;
	}
	if (!*node)
	{
		printf("Error: unclosed quote \n");
		g_exit_status = 2;
		return (true);
	}
	return (false);
}

bool	check_syntax(t_compo *tokenes_lst)
{
	t_compo	*node;

	node = tokenes_lst;
	while (node)
	{
		if (node->type == PIPE)
		{
			if (check_pipe_syn(node))
				return (true);
		}
		else if (is_redir(node->type))
		{
			if (check_redir_syn(node))
				return (true);
		}
		else if (node->type == SQUOTE || node->type == DQUOTE)
		{
			if (check_quote_syn(&node, node->type))
				return (true);
		}
		node = node->next;
	}
	return (false);
}
