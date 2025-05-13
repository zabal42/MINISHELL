/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabal-m <mzabal-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:43:20 by mzabal-m          #+#    #+#             */
/*   Updated: 2025/05/12 12:03:14 by mzabal-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft/inc/libft.h"

//Devuelve 1 si el carácter es un espacio en blanco reconocido por el shell.
int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

//Devuelve 1 si el carácter es un símbolo de redirección (< o >)
int	is_redirect_char(char c)
{
	return (c == '<' || c == '>');
}

//Devuelve 1 si el carácter es un metacarácter (usado para dividir tokens)
int	is_metachar(char c)
{
	return (c == '|' || is_redirect_char(c));
}

//Devuelve 1 si el carácter es una comilla simple o doble
int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

