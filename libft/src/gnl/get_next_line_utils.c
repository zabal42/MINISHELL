/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelzabal <mikelzabal@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:07:53 by mzabal-m          #+#    #+#             */
/*   Updated: 2024/12/24 11:55:04 by mikelzabal       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>

int	ft_strlen_gnl(const char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (*str++)
		len++;
	return (len);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (0);
}

char	*ft_strdup_gnl(const char *s1)
{
	char	*dup;
	char	*ptr;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen_gnl(s1);
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	ptr = dup;
	while (*s1)
		*ptr++ = *s1++;
	*ptr = '\0';
	return (dup);
}

char	*ft_gnlstrjoin(char *s1, const char *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;

	if (!s1)
		s1 = ft_strdup_gnl("");
	if (!s2)
		s2 = "";
	dest = malloc((ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1) * sizeof(char));
	if (!dest)
	{
		free(s1);
		return (NULL);
	}
	i = -1;
	while (s1[++i])
		dest[i] = s1[i];
	j = 0;
	while (s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
	free(s1);
	return (dest);
}
