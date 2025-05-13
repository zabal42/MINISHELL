/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_futoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabal-m <mzabal-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:33:16 by mzabal-m          #+#    #+#             */
/*   Updated: 2025/03/04 15:05:54 by mzabal-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include "libft.h"

char	*ft_futoa(unsigned long long num, const char *digits)
{
	char				*result;
	int					len;
	int					base;
	unsigned long long	temp;

	if (!digits || ft_strlen_printf(digits) == 0)
		return (NULL);
	if (num == 0)
		return (ft_strdup("0"));
	base = ft_strlen_printf(digits);
	temp = num;
	len = 0;
	while (temp > 0 && ++len)
		temp /= base;
	result = (char *)ft_calloc_pf_printf(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (num > 0)
	{
		result[--len] = digits[num % base];
		num /= base;
	}
	return (result);
}
//he tenido que reducirla porque se pasaba de lineas!!
/*en el 
		while (temp > 0 && ++len)
			temp /= base;
		es lo mismo que:
		while (temp > 0)
		{
			++len;
			temp /= base;
		}
		*/