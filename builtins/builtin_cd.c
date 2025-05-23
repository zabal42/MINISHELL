/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:05:58 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/21 11:06:40 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	select_path(t_shell *shell, t_cmd *cmd, char **path)
{
	if (!cmd->argv[1] || ft_strncmp(cmd->argv[1], "~", 1) == 0)
	{
		*path = get_key_value("HOME", shell);
		if (!*path)
		{
			printf("cd: HOME not set");
			return (1);
		}
	}
	else if (ft_strncmp(cmd->argv[1], "-", 1) == 0)
	{
		*path = get_key_value("OLDPWD", shell);
		if (!*path)
		{
			printf("cd: OLDPWD not set");
			return (1);
		}
	}
	else
		*path = cmd->argv[1];
	return (0);
}

int	ft_cd(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	char	*oldpwd;
	char	*pwd;

	path = NULL;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("getcwd"), 1);
	if (select_path(shell, cmd, &path))
	{
		free(oldpwd);
		return (1);
	}
	update_env_variable(shell, "OLDPWD", oldpwd);
	free(oldpwd);
	if (chdir(path) != 0)
		return (perror("chdir"), 1);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("getcwd"), 1);
	update_env_variable(shell, "PWD", pwd);
	free(pwd);
	return (0);
}

char	*get_key_value(char *key, t_shell *shell)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], key, len) == 0
			&& shell->envp[i][len] == '=')
			return (&shell->envp[i][len + 1]);
		i++;
	}
	return (NULL);
}

void	update_env_variable(t_shell *shell, char *key, char *new_value)
{
	int		i;
	int		len;
	char	*new_entry;

	len = ft_strlen(key);
	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], key, len) == 0
			&& shell->envp[i][len] == '=')
		{
			new_entry = ft_strjoin(key, "=");
			if (!new_entry)
				return ;
			shell->envp[i] = ft_strjoin(new_entry, new_value);
			free(new_entry);
			return ;
		}
		i++;
	}
}
