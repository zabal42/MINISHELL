/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabal-m <mzabal-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:39:12 by mzabal-m          #+#    #+#             */
/*   Updated: 2024/12/03 09:33:39 by mzabal-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_word_count(const char *str, char delim)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != delim && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*str == delim)
			in_word = 0;
		str++;
	}
	return (count);
}

static void	*ft_free_all(char **result, int i)
{
	while (i >= 0)
	{
		free(result[i]);
		i--;
	}
	free(result);
	return (NULL);
}

static const char	*next_word(const char *str, char delim, int *len)
{
	const char	*start;

	while (*str && *str == delim)
		str++;
	start = str;
	while (*str && *str != delim)
		str++;
	*len = str - start;
	return (start);
}

static int	fill_words(char **result, const char *str, char delim, int words)
{
	const char	*start;
	int			len;
	int			i;

	i = 0;
	while (i < words)
	{
		start = next_word(str, delim, &len);
		if (len > 0)
		{
			result[i] = ft_substr(start, 0, len);
			if (!result[i])
			{
				ft_free_all(result, i - 1);
				return (0);
			}
			i++;
		}
		str = start + len;
	}
	result[i] = NULL;
	return (1);
}

char	**ft_split(const char *str, char delim)
{
	char	**result;
	int		words;

	if (!str)
		return (NULL);
	words = ft_word_count(str, delim);
	result = (char **)ft_calloc(words + 1, sizeof(char *));
	if (!result)
		return (NULL);
	if (!fill_words(result, str, delim, words))
		return (NULL);
	return (result);
}
