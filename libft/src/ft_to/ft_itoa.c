/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabal-m <mzabal-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:31:26 by mzabal-m          #+#    #+#             */
/*   Updated: 2024/12/03 11:18:47 by mzabal-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_itoa_len(long n)
{
	int	len;

	len = 1;
	while (n / 10 != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static long	ft_handle_negatives(int n, int *neg)
{
	long	num;

	num = (long)n;
	if (num < 0)
	{
		*neg = 1;
		return (-num);
	}
	*neg = 0;
	return (num);
}

char	*ft_itoa(int n)
{
	long	num;
	int		len;
	int		neg;
	char	*str;

	num = ft_handle_negatives(n, &neg);
	len = ft_itoa_len(num) + neg;
	str = (char *)ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len > neg)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
	if (neg)
		str[0] = '-';
	return (str);
}
