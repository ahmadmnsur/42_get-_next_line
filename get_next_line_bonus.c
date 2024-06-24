/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmmanso <ahmmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:35:14 by ahmmanso          #+#    #+#             */
/*   Updated: 2024/06/22 18:47:14 by ahmmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free(char *s, char *buff)
{
	char	*temp;

	temp = ft_strjoin(s, buff);
	free(s);
	return (temp);
}

char	*ft_read_str(int fd, char *s)
{
	char	*buff;
	int		bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	if (!s)
	{
		s = malloc(1);
		if (!s)
			return (free(buff), NULL);
		s[0] = '\0';
	}
	bytes = 1;
	while (!ft_strchr(s, '\n') && bytes != 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
			return (free(buff), free(s), NULL);
		buff[bytes] = '\0';
		s = ft_free(s, buff);
		if (!s)
			return (free(buff), NULL);
	}
	return (free(buff), s);
}

char	*get_next_line(int fd)
{
	char		*first_line;
	static char	*str[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str[fd] = ft_read_str(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	first_line = ft_get_line(str[fd]);
	str[fd] = ft_new_str(str[fd]);
	return (first_line);
}
