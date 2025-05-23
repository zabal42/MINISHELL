/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelzabal <mikelzabal@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:06:10 by mikelzabal        #+#    #+#             */
/*   Updated: 2025/05/23 09:14:12 by mikelzabal       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include "parser.h"

// Combina dos strings, liberando el primero
char *ft_strjoin_free(char *s1, const char *s2)
{
	char *joined;
	if (!s1 || !s2)
		return (NULL);
	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

/*
** get_env_value:
** Busca en el array `envp` una variable cuyo nombre coincida con `name`.
** Si encuentra una coincidencia exacta (ej: USER=...), devuelve solo el valor.
** Si no existe, retorna NULL.
*/
static char	*get_env_value(const char *name, char **envp)
{
	size_t	len = ft_strlen(name);
	int		i = 0;

	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1); // Salta el nombre y el '='
		i++;
	}
	return (NULL);
}

/*
** expand_status_code:
** Sustituye `$?` por el valor del último exit status (`last_status`).
** Convierte ese número a string y lo concatena al resultado actual.
*/
char	*expand_status_code(char *result, int last_status)
{
	char	*status_str = ft_itoa(last_status);
	char	*joined = ft_strjoin_free(result, status_str);
	free(status_str);
	return (joined);
}

/*
** expand_env_variable:
** Lee el nombre de la variable desde `str[*i]` hasta que deje de ser alfanumérico o '_'.
** Busca ese nombre en `envp` y concatena su valor al resultado.
** Avanza el índice `*i` hasta el final del nombre de la variable.
*/
char	*expand_env_variable(char *result, const char *str, size_t *i, char **envp)
{
	size_t	start = *i;

	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	char	*var = ft_substr(str, start, *i - start);
	char	*val = get_env_value(var, envp);
	char	*joined = ft_strjoin_free(result, val ? val : "");
	free(var);
	return (joined);
}

/*
** expand_variables:
** Función principal que analiza la cadena `str` y expande:
** - `$VAR` usando `envp`
** - `$?` con `last_status`
** Concatena el resultado expandido y lo devuelve como nuevo string.
** Se ignoran comillas aquí (debes manejarlas antes o después).
*/
char	*expand_variables(const char *str, char **envp, int last_status)
{
	char	*result = ft_strdup(""); // Resultado final
	size_t	i = 0;
	char	tmp[2];

	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '?')
			{
				result = expand_status_code(result, last_status);
				i++;
			}
			else
				result = expand_env_variable(result, str, &i, envp);
		}
		else
		{
			tmp[0] = str[i++];
			tmp[1] = '\0';
			result = ft_strjoin_free(result, tmp);
		}
	}
	return (result);
}