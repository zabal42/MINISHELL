/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabal-m <mzabal-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 09:10:57 by zabal             #+#    #+#             */
/*   Updated: 2024/12/02 13:08:36 by mzabal-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	s_len;

	if (!s1 || !s2)
		return (NULL);
	s_len = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *)ft_calloc((s_len + 1), sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1, s_len + 1);
	ft_strlcat(dest, s2, s_len + 1);
	return (dest);
}

/*char	*ft_strjoin(char const *s1, char const *s2)
{
	char 	*dest;
	char	*ptr;
	size_t	s_len;

	if (!s1 || !s2)
		return (NULL);
	s_len = ft_strlen(s1) + ft_strlen(s2);
	
	dest = (char*)malloc(sizeof(char) * (s_len + 1));
	if (!dest)
		return (NULL);
	ptr = dest;
	while (*s1)
		*ptr++ = *s1++;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	return (dest);
}
*/