/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hex_lower.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabal-m <mzabal-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:18:55 by mzabal-m          #+#    #+#             */
/*   Updated: 2025/03/04 15:07:10 by mzabal-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <unistd.h>

int	handle_hex_lower(unsigned int num)
{
	char	*str;
	int		len;

	str = ft_futoa(num, "0123456789abcdef");
	ft_putstr_printf(str);
	len = ft_strlen_printf(str);
	free(str);
	return (len);
}
