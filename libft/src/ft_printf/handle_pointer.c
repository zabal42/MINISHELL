/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabal-m <mzabal-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:02:06 by mzabal-m          #+#    #+#             */
/*   Updated: 2025/03/04 15:07:27 by mzabal-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <unistd.h>

int	handle_pointer(void *ptr)
{
	int		len;
	char	*hex_str;

	if (!ptr)
		return (write(1, "(nil)", 5));
	write(1, "0x", 2);
	hex_str = ft_futoa((unsigned long long)ptr, "0123456789abcdef");
	if (!hex_str)
		return (-1);
	len = write(1, hex_str, ft_strlen_printf(hex_str)) + 2;
	free (hex_str);
	return (len);
}
