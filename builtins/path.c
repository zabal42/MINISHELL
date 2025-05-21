/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:27:56 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/21 13:19:45 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_executable(char *command, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	i = 0;
	path_env = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		if (!full_path)
			return (free_array(paths), full_path);
		full_path = ft_strjoin(full_path, command);
		if (access(full_path, X_OK) == 0)
			return (free_array(paths), full_path);
		free(full_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
