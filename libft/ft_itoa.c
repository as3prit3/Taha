/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:33:52 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/16 18:42:06 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_nb(int n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int			sign;
	long long	nb;
	char		*str;
	size_t		count;

	nb = n;
	count = count_nb(nb);
	sign = 0;
	str = malloc(count + 1 + (nb < 0));
	if (!str)
		return (NULL);
	str[count + (nb < 0)] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		sign = 1;
		nb = -nb;
	}
	while (count--)
	{
		str[count + sign] = (nb % 10) + 48;
		nb /= 10;
	}
	return (str);
}
