/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:25:26 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/29 16:10:47 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_gnl_strchr(char *str, int c)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	if (c == 0)
		return (1);
	return (0);
}

char	*ft_join(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	if (!s2)
		return (free(s1), NULL);
	str = malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (free(s1), NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

// static int	is_in_set(char c, const char *set)
// {
// 	while (*set)
// 	{
// 		if (*set == c)
// 			return (1);
// 		set++;
// 	}
// 	return (0);
// }

// char	*ft_strtrim(char *s1, char const *set)
// {
// 	char	*str;
// 	int		start;
// 	int		end;
// 	int		i;

// 	start = 0;
// 	if (!s1 || !set)
// 		return (NULL);
// 	end = ft_strlen(s1) - 1;
// 	while (is_in_set(s1[start], set) && s1[start])
// 		start++;
// 	while (end > start && is_in_set(s1[end], set))
// 		end--;
// 	i = 0;
// 	str = malloc((end - start + 1) + 1);
// 	if (!str)
// 		return (NULL);
// 	while (i < (end - start + 1))
// 	{
// 		str[i] = s1[start + i];
// 		i++;
// 	}
// 	str[i] = '\0';
// 	free(s1);
// 	return (str);
// }
