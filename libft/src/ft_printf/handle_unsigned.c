/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabal-m <mzabal-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:14:00 by mzabal-m          #+#    #+#             */
/*   Updated: 2025/03/04 15:07:36 by mzabal-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <unistd.h>

int	handle_unsigned(unsigned int num)
{
	char	*str;
	int		len;

	if (num == 0)
		return (write(1, "0", 1));
	str = ft_futoa(num, "0123456789");
	ft_putstr_printf(str);
	len = ft_strlen_printf(str);
	free(str);
	return (len);
}
