/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:00:37 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/07/11 16:43:11 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_next_line(char *str)
{
	int		i;
	int		j;
	char	*s;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	s = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!s)
		return (NULL);
	while (str[i])
		s[j++] = str[i++];
	s[j] = '\0';
	free(str);
	return (s);
}

static char	*ft_put_line(char *str, char *buff, int j)
{
	while (str[j])
	{
		if (str[j] == '\n')
		{
			buff[j++] = '\n';
			buff[j] = '\0';
			return (buff);
		}
		buff[j] = str[j];
		j++;
	}
	buff[j] = '\0';
	return (buff);
}

static char	*ft_get_line(char *str)
{
	int		i;
	int		j;
	char	*buff;

	i = 0;
	j = 0;
	if (!*str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	buff = malloc(sizeof(char) * i + 1);
	if (!buff)
		return (NULL);
	buff = ft_put_line(str, buff, j);
	return (buff);
}

static char	*ft_read_file(char *str, int fd)
{
	ssize_t	read_bytes;
	char	*res;

	res = malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!res)
		return (NULL);
	read_bytes = 1;
	while (!ft_gnl_strchr(str, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, res, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(res);
			free(str);
			return (NULL);
		}
		res[read_bytes] = '\0';
		str = ft_join(str, res);
	}
	free(res);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buffer;

	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	str = ft_read_file(str, fd);
	if (str == NULL)
		return (NULL);
	buffer = ft_get_line(str);
	str = ft_next_line(str);
	return (buffer);
}
