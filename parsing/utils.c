/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:46:57 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/29 00:18:51 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*ft_cmdnew(int in, int out, t_list *lst_cmd)
{
	t_cmd	*new;
	t_list	*tmp;
	char	**args;
	int		i;

	i = 0;
	tmp = lst_cmd;
	args = (char **)malloc(sizeof(char *) * (ft_lstsize(lst_cmd) + 1));
	if (!args)
		return (NULL);
	while (tmp)
	{
		args[i++] = ft_strdup((char *)tmp->content);
		tmp = tmp->next;
	}
	args[i] = NULL;
	if (!args[0])
		return (free(args), NULL);
	new = malloc(sizeof(t_cmd));
	new->args = args;
	new->in_file = in;
	new->out_file = out;
	new->next = NULL;
	return (new);
}

void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*tmp;

	if (!*cmd)
	{
		*cmd = new;
		return ;
	}
	tmp = *cmd;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	create_cmd(t_data *data)
{
	ft_cmdadd_back(&data->cmd, ft_cmdnew(data->in, data->out, data->lst_cmd));
	if (data->lst_cmd)
		ft_lstclear(&data->lst_cmd, free);
	data->in = 0;
	data->out = 1;
}

void	ft_cmd_clear(t_cmd **lst)
{
	t_cmd	*next;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		ft_free2d((*lst)->args);
		free(*lst);
		*lst = next;
	}
	*lst = NULL;
}

int	ft_cmdsize(t_cmd *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
