/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:05:58 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/13 09:40:17 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **copy_env(char **envp)
{
	int		i;
	int		j;
	char	**env_copy;

	i = 0;
	j = 0;
	while (envp[i])
		i++;
	env_copy = (char **)malloc((i + 1) * sizeof(char *));
	if (!env_copy)
		return (NULL);
	while (j < i)
	{
		env_copy[j] = ft_strdup(envp[j]);
		j++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}

void free_env(char **env_copy)
{
	int i;

	i = 0;
	while (env_copy[i])
		free(env_copy[i++]);
	free(env_copy);
}
