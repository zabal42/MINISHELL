/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabal-m <mzabal-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:29:16 by mzabal-m          #+#    #+#             */
/*   Updated: 2025/03/04 15:07:22 by mzabal-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <unistd.h>

int	handle_int(int num)
{
	char	*str;
	int		len;

	len = 0;
	if (num == 0)
		return (write(1, "0", 1));
	if (num < 0)
		str = ft_futoa(-(unsigned long long)num, "0123456789");
	else
		str = ft_futoa((unsigned long long)num, "0123456789");
	if (!str)
	{
		free(str);
		return (-1);
	}
	if (num < 0)
	{
		write (1, "-", 1);
		len = 1;
	}
	ft_putstr_printf(str);
	len += ft_strlen_printf(str);
	free(str);
	return (len);
}
