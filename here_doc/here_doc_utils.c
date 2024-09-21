/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:58:09 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/30 10:14:45 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	write_to_file(int fd, t_compo *tmp)
{
	while (tmp)
	{
		write(fd, tmp->content, ft_strlen(tmp->content));
		tmp = tmp->next;
	}
}

char	*update_content(char *content, char *line)
{
	char	*tmp2;
	char	*new_content;

	tmp2 = ft_strjoin(content, line);
	free(content);
	new_content = ft_strjoin(tmp2, "\n");
	free(tmp2);
	return (new_content);
}

void	init_here_doc_var(int *i, char **content, t_data *data, t_compo **token)
{
	*i = 0;
	*content = NULL;
	data->delim = get_delimiter(token, i, data);
}

void	signalhanlder(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		exit(130);
	}
}

char	*get_quote_delimiter(t_compo **lex, enum e_type type)
{
	char	*s;
	char	*tmp;

	*lex = (*lex)->next;
	s = NULL;
	while (*lex)
	{
		if (!s)
			s = ft_strdup("");
		if ((*lex)->next && (*lex)->type == type && (*lex)->next->type == type)
			(*lex) = (*lex)->next;
		else if ((*lex)->type != type)
		{
			tmp = s;
			s = ft_strjoin(tmp, (*lex)->content);
			free(tmp);
		}
		else
			break ;
		if (*lex)
			*lex = (*lex)->next;
	}
	return (s);
}
