/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hex_upper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabal-m <mzabal-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:23:58 by mzabal-m          #+#    #+#             */
/*   Updated: 2025/03/04 15:07:14 by mzabal-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <unistd.h>

int	handle_hex_upper(unsigned int num)
{
	char	*str;
	int		len;

	str = ft_futoa(num, "0123456789ABCDEF");
	ft_putstr_printf(str);
	len = ft_strlen_printf(str);
	free(str);
	return (len);
}
