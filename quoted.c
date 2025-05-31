/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelzabal <mikelzabal@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:28:51 by mikelzabal        #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/31 13:12:58 by mikelzabal       ###   ########.fr       */
=======
/*   Updated: 2025/05/31 13:14:53 by mzabal-m         ###   ########.fr       */
>>>>>>> 3d9c93cd3d5f0caeba8117e930e8f2bbfdd8f023
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/inc/libft.h"
#include "parser.h"

/*
** extract_one_quoted:
** Extrae el contenido entre comillas (simples o dobles)
** a partir de la posición actual.
** Avanza el índice hasta la comilla de cierre y
** devuelve el contenido entre ellas.
** Si no encuentra comilla de cierre, devuelve NULL.
*/
char	*extract_one_quoted(const char *line, size_t *i)
{
	size_t	start;
	size_t	len;
	char	quote;

	quote = line[*i];
	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (!line[*i])
		return (NULL);
	len = *i - start;
	(*i)++;
	return (ft_substr(line, start, len));
}
/*
** safe_strjoin:
** Une dos strings en uno nuevo usando ft_strjoin.
** Si alguno de los dos es NULL, devuelve NULL.
** No libera los argumentos (se espera que quien la use controle eso).
*/

char	*safe_strjoin(char *s1, char *s2)
{
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	joined = ft_strjoin(s1, s2);
	if (!joined)
		return (NULL);
	return (joined);
}
/*
** concat_quoted_segments:
** Concatena múltiples segmentos entre comillas seguidos.
** - Avanza el índice `i` en cada quoted string detectada.
** - Termina cuando el siguiente carácter ya no es una comilla,
**	espacio o metacaracter.
*/

static char	*extract_unquoted_segment(const char *line, size_t *i)
{
	size_t	start;

	start = *i;
	while (line[*i] && !is_quote(line[*i]) && !is_space(line[*i])
		&& !is_metachar(line[*i]))
		(*i)++;
	return (ft_substr(line, start, *i - start));
}

static int	append_segment(char **result, char *next)
{
	char	*temp;

	if (!*result)
	{
		*result = next;
		return (1);
	}
	temp = safe_strjoin(*result, next);
	free(*result);
	free(next);
	if (!temp)
	{
		*result = NULL;
		return (0);
	}
	*result = temp;
	return (1);
}

char	*concat_quoted_segments(const char *line, size_t *i)
{
	char	*result;
	char	*next;

	result = NULL;
	while (line[*i])
	{
		if (is_quote(line[*i]))
			next = extract_one_quoted(line, i);
		else if (!is_metachar(line[*i]) && !is_space(line[*i]))
			next = extract_unquoted_segment(line, i);
		else
			break ;
		if (!next || !append_segment(&result, next))
			return (free(result), NULL);
	}
	return (result);
}
