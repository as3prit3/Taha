/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:58:15 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/30 10:15:14 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_file_name(void)
{
	int		fd;
	char	buff[11];
	char	*arr;
	int		i;
	int		n;

	fd = open("/dev/random", O_RDONLY, 0777);
	if (fd == -1)
		return (NULL);
	if (read(fd, buff, 10) == -1)
		return (NULL);
	buff[10] = 0;
	arr = "0123456789abcdef";
	i = -1;
	while (++i < 10)
	{
		if (buff[i] < 0)
			buff[i] *= -1;
		buff[i] = buff[i] % 16;
		n = buff[i];
		buff[i] = arr[n];
	}
	close(fd);
	return (ft_strjoin("/tmp/", buff));
}

char	*get_delimiter(t_compo **token, int *i, t_data *data)
{
	char	*delim;

	*token = skip_spaces(*token, 1);
	(void)data;
	if (!*token)
		return (NULL);
	if ((*token)->type == SQUOTE || (*token)->type == DQUOTE)
	{
		delim = get_quote_delimiter(token, (*token)->type);
		*i = 1;
		return (delim);
	}
	delim = ft_strdup((*token)->content);
	return (delim);
}

void	process_line(t_data *data, t_compo **tmp, int fd, int i)
{
	t_compo	*curr;

	if (!*tmp)
		return ;
	curr = *tmp;
	while (curr)
	{
		if ((curr->type == ENV || curr->type == EX_STATUS) && i == 0)
			parse_env(data, &curr);
		else if ((curr->state == IN_DQUOTE || curr->state == IN_SQUOTE)
			&& curr->type == WORD)
		{
			if (curr->content[0] == '$' && i == 0)
				parse_env(data, &curr);
		}
		else if ((curr->state == IN_DQUOTE || curr->state == IN_SQUOTE)
			&& (curr->type == ENV || curr->type == EX_STATUS) && i == 0)
			parse_env(data, &curr);
		curr = curr->next;
	}
	write_to_file(fd, *tmp);
}

void	here_doc(t_data *data, t_compo **token)
{
	int		fd;
	char	*line;
	t_compo	*tmp;
	char	*content;
	int		i;

	init_here_doc_var(&i, &content, data, token);
	fd = open(data->name, O_CREAT | O_RDWR | O_APPEND, 0644);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, data->delim))
		{
			free(line);
			free(data->delim);
			tmp = lexer(content);
			process_line(data, &tmp, fd, i);
			free_list(tmp);
			free(content);
			break ;
		}
		content = update_content(content, line);
		free(line);
	}
	close(fd);
}

void	child_here_doc(t_data *data, t_compo **token, char **str)
{
	int		st;

	signal(SIGINT, SIG_IGN);
	*token = skip_spaces(*token, 1);
	data->name = get_file_name();
	data->pid = fork();
	if (data->pid == 0)
	{
		signal(SIGINT, signalhanlder);
		here_doc(data, token);
		free_here_doc(data, *str);
		exit(0);
	}
	wait(&st);
	if (WEXITSTATUS(st) == 130)
	{
		g_exit_status = 130;
		data->error = 1;
	}
	data->in = open(data->name, O_RDONLY, 0644);
	ft_lstadd_back(&data->here_doc_name, ft_lstnew(ft_strdup(data->name)));
	free(data->name);
}
