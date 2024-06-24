/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmmanso <ahmmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:38:07 by ahmmanso          #+#    #+#             */
/*   Updated: 2024/06/22 17:38:08 by ahmmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *str, int c)
{
	char	ch;

	ch = (char) c;
	if (ch == '\0')
		return ((char *) str);
	while (*str)
	{
		if (*str == ch)
			return ((char *) str);
		str++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	index;
	size_t	str_1_len;
	char	*new_str;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	str_1_len = ft_strlen(s1);
	new_str = (char *)malloc(sizeof(char) * ft_strlen(s2) + str_1_len + 1);
	if (!new_str)
		return (NULL);
	index = 0;
	while (s1[index])
	{
		new_str[index] = s1[index];
		index++;
	}
	while (s2[index - str_1_len])
	{
		new_str[index] = s2[index - str_1_len];
		index++;
	}
	return (new_str[index] = '\0', new_str);
}

size_t	ft_strlen(const char *a)
{
	size_t	i;

	i = 0;
	while (a[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_get_line(char *s)
{
	size_t	i;
	char	*line;

	if (!s[0])
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = -1;
	while (i++, s[i] && s[i] != '\n')
		line[i] = s[i];
	if (s[i] == '\n')
	{
		line[i] = s[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_new_str(char *s)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	new_str = malloc(ft_strlen(s) - i + 1);
	if (!new_str)
		return (NULL);
	i++;
	j = 0;
	while (s[i])
		new_str[j++] = s[i++];
	new_str[j] = '\0';
	return (free(s), new_str);
}
