/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:05:58 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/13 13:12:34 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_key_value(char *key, char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
			return (&envp[i][len + 1]);
		i++;
	}
	return (NULL);
}

static void	update_env_variable(char **envp, char *key, char *new_value)
{
	int		i;
	int		len;
	char	*new_entry;

	len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
		{
			free(envp[i]);
			new_entry = ft_strjoin(key, "=");
			envp[i] = ft_strjoin(new_entry, new_value);
			free(new_entry);
			return ;
		}
		i++;
	}
}

int	ft_cd(char **args, char **envp)
{
	char	*path;
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 0);
	if (!args[1])
	{
		path = get_key_value("HOME", envp);
		if (!path)
		{
			printf("cd: HOME not set");
			return (1);
		}
	}
	else if (ft_strncmp(args[1], "-", 1) == 0)
	{
		path = get_key_value("OLDPWD", envp);
		if (!path)
		{
			printf("cd: OLDPWD not set");
			return (1);
		}
		printf("%s\n", path);
	}
	else
	{
		path = args[1];
	}
	update_env_variable(envp, "OLDPWD", oldpwd);
	if (chdir(path) != 0)
		return (1);
	pwd = getcwd(NULL, 0);
	update_env_variable(envp, "PWD", pwd);
	return (0);
}
