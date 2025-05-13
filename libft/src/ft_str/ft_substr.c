/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabal-m <mzabal-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:12:23 by zabal             #+#    #+#             */
/*   Updated: 2024/12/02 13:05:04 by mzabal-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	char	*src;
	char	*ptr;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	dest = (char *)ft_calloc((len + 1), (sizeof(char)));
	if (!dest)
		return (NULL);
	src = (char *)s + start;
	ptr = dest;
	while (len-- && *src)
		*ptr++ = *src++;
	*ptr = '\0';
	return (dest);
}
