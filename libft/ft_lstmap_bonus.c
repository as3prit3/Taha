/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:43:14 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/16 18:42:20 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*res_list;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	res_list = NULL;
	while (lst)
	{
		content = f(lst->content);
		new_node = ft_lstnew(content);
		if (!new_node)
		{
			ft_lstclear(&res_list, del);
			del(content);
			return (NULL);
		}
		ft_lstadd_back(&res_list, new_node);
		lst = lst->next;
	}
	return (res_list);
}
