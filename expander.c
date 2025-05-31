/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelzabal <mikelzabal@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:06:10 by mikelzabal        #+#    #+#             */
/*   Updated: 2025/05/31 12:46:48 by mikelzabal       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include "parser.h"

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

static char	*get_env_value(const char *name, char **envp)
{
	size_t	len;
	int		i;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*expand_status_code(char *result, int last_status)
{
	char	*status_str;
	char	*joined;

	status_str = ft_itoa(last_status);
	joined = ft_strjoin_free(result, status_str);
	free(status_str);
	return (joined);
}

char	*expand_env_variable(char *result, const char *str,
		size_t *i, char **envp)
{
	size_t	start;
	char	*var;
	char	*val;
	char	*joined;

	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var = ft_substr(str, start, *i - start);
	val = get_env_value(var, envp);
	if (val)
		joined = ft_strjoin_free(result, val);
	else
		joined = ft_strjoin_free(result, "");
	free(var);
	return (joined);
}

static char	*handle_dollar_expression(const char *str, size_t *i, char **envp,
		int last_status)
{
	char	*result;

	result = NULL;
	if (str[*i] == '?')
	{
		result = expand_status_code(ft_strdup(""), last_status);
		(*i)++;
	}
	else
		result = expand_env_variable(ft_strdup(""), str, i, envp);
	return (result);
}

char	*expand_variables(const char *str, char **envp, int last_status)
{
	char	*result;
	size_t	i;
	char	tmp[2];
	char	*expansion;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			expansion = handle_dollar_expression(str, &i, envp, last_status);
			result = ft_strjoin_free(result, expansion);
			free(expansion);
		}
		else
		{
			tmp[0] = str[i];
			tmp[1] = '\0';
			i++;
			result = ft_strjoin_free(result, tmp);
		}
	}
	return (result);
}
