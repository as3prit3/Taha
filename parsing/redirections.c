/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:51:19 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/27 14:10:25 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_redir_error(t_list *lst, t_data *data)
{
	t_list	*tmp;
	int		size;

	if (!lst)
		return ;
	tmp = lst;
	size = ft_cmdsize(data->cmd);
	if (size == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((char *)tmp->content, 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		while (tmp)
		{
			ft_putstr_fd(tmp->content, 2);
			ft_putstr_fd("\n", 2);
			tmp = tmp->next;
		}
	}
}

void	redir_error(t_data *data, char *str)
{
	char	*tmp;
	char	*tmp2;

	if (data->exp_status == 1 && data->expend)
	{
		tmp = ft_strjoin(data->expend, ": ambiguous redirect");
		ft_lstadd_back(&data->lst_err, ft_lstnew(ft_strdup(tmp)));
		free(tmp);
		data->exp_status = 0;
	}
	else
	{
		tmp = ft_strdup(str);
		tmp2 = ft_strjoin(tmp, ": ");
		free(tmp);
		tmp = ft_strjoin(tmp2, "No such file or directory");
		free(tmp2);
		ft_lstadd_back(&data->lst_err, ft_lstnew(ft_strdup(tmp)));
		free(tmp);
	}
	if (data->expend)
	{
		free(data->expend);
		data->expend = NULL;
	}
}

void	in_file(t_data *data, char *str)
{
	if (data->in != -1)
	{
		if (!str[0])
		{
			redir_error(data, NULL);
			data->in = -1;
		}
		else
		{
			if (data->in > 2)
				close(data->in);
			data->in = open(str, O_RDONLY, 0644);
			if (data->in == -1)
				redir_error(data, str);
		}
	}
}

void	out_file(t_data *data, char *str)
{
	if (data->in != -1 && data->out != -1)
	{
		if (!str[0])
		{
			redir_error(data, NULL);
			data->out = -1;
		}
		else
		{
			if (data->out > 2)
				close(data->out);
			data->out = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (data->out == -1)
				redir_error(data, str);
		}
	}
}

void	append(t_data *data, char *str)
{
	if (data->out != -1)
	{
		if (!str[0])
		{
			redir_error(data, NULL);
			data->out = -1;
		}
		else
		{
			if (data->in > 2)
				close(data->in);
			data->out = open(str, O_RDWR | O_CREAT | O_APPEND, 0644);
			if (data->out == -1)
				redir_error(data, str);
		}
	}
}
