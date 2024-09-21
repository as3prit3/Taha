/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:26:38 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/29 00:19:32 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_special(char c)
{
	return (c == '\'' || c == '\"' || c == '|' || c == '<' || c == '$'
		|| c == '>' || ft_space(c) || c == '\n' || c == '\0');
}

void	print(t_compo *list)
{
	t_compo	*node;

	node = list;
	while (node)
	{
		printf("content: %s", node->content);
		printf(", state: %u", node->state);
		printf(", type: %u\n", node->type);
		node = node->next;
	}
}

int	tokenize(t_compo **tokens_lst, char *line, int i, enum e_state *state)
{
	if (!is_special(line[i]))
		i += get_word(tokens_lst, line + i, *state);
	else if (line[i] == '\'' || line[i] == '\"')
		get_quote(tokens_lst, line + i++, state);
	else if (line[i] == '<' || line[i] == '>')
		i += get_redirection(tokens_lst, line, i, *state);
	else if (line[i] == '$')
	{
		if ((ft_space(line[i + 1]) || line[i + 1] == '$')
			&& (line[i + 1] != '\'' || line[i + 1] != '\"'))
		{
			add_to_list(tokens_lst, new_comp(line + i++, 2, *state, WORD));
			i++;
		}
		else
			i += get_env(tokens_lst, line + i, *state);
	}
	else if (line[i] == '|')
		add_to_list(tokens_lst, new_comp(line + (i++), 1, *state, PIPE));
	else if (ft_space(line[i]))
		add_to_list(tokens_lst, new_comp(line + (i++), 1, *state, W_SPACE));
	return (i);
}

t_compo	*lexer(char *line)
{
	t_compo			*tokens_lst;
	enum e_state	state;
	int				i;

	if (!line)
		return (NULL);
	i = 0;
	state = GENERAL;
	tokens_lst = NULL;
	while (line[i])
		i = tokenize(&tokens_lst, line, i, &state);
	return (tokens_lst);
}
