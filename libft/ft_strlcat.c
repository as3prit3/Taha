/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:16:54 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/16 18:38:09 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dest;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	len_dest = ft_strlen(dest);
	if (size <= len_dest)
		return (ft_strlen(src) + size);
	while (src[i] && len_dest < size - 1)
	{
		dest[len_dest++] = src[i];
		i++;
	}
	dest[len_dest] = '\0';
	return (len_dest + ft_strlen(src + i));
}
