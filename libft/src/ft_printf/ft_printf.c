/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabal-m <mzabal-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:36:47 by mzabal-m          #+#    #+#             */
/*   Updated: 2025/03/04 15:06:15 by mzabal-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stdarg.h>

static int	handle_format(char format, va_list args)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += handle_char(va_arg(args, int));
	else if (format == 's')
		len += handle_string(va_arg(args, char *));
	else if (format == 'p')
		len += handle_pointer(va_arg(args, void *));
	else if (format == 'u')
		len += handle_unsigned(va_arg(args, unsigned int));
	else if (format == 'x')
		len += handle_hex_lower(va_arg(args, unsigned int));
	else if (format == 'X')
		len += handle_hex_upper(va_arg(args, unsigned int));
	else if (format == 'd' || format == 'i')
		len += handle_int(va_arg(args, int));
	else
		len += handle_char('%');
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		total_len;

	va_start(args, format);
	total_len = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format)
				total_len += handle_format(*format, args);
			else
				break ;
		}
		else
		{
			total_len += write(1, format, 1);
		}
		format++;
	}
	va_end(args);
	return (total_len);
}
