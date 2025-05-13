/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabal-m <mzabal-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 12:54:20 by zabal             #+#    #+#             */
/*   Updated: 2024/12/02 13:11:02 by mzabal-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(const char *s1, const char *set)
{
	const char	*start;
	const char	*end;
	char		*trimmed;
	char		*result;

	if (!s1 || !set)
		return (NULL);
	start = s1;
	while (*start && ft_strchr(set, *start))
		start++;
	end = s1 + ft_strlen(s1);
	while (end > start && ft_strchr(set, *(end - 1)))
		end--;
	trimmed = (char *)ft_calloc(((end - start) + 1), sizeof(char));
	if (!trimmed)
		return (NULL);
	result = trimmed;
	while (start < end)
		*trimmed++ = *start++;
	*trimmed = '\0';
	return (result);
}
