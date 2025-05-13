/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabal-m <mzabal-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:50:56 by mzabal-m          #+#    #+#             */
/*   Updated: 2025/03/04 15:07:31 by mzabal-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <unistd.h>

int	handle_string(char *str)
{
	if (!str)
	{
		ft_putstr_printf("(null)");
		return (6);
	}
	ft_putstr_printf(str);
	return (ft_strlen_printf(str));
}
