/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:11:52 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/16 18:42:57 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len_str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len_str = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(len_str + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, len_str + 1);
	ft_strlcat(str, s2, len_str + 1);
	return (str);
}
