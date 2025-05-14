/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:05:58 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/14 13:11:56 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
static char	*get_key_value(char *key, t_shell *shell)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], key, len) == 0 &&
			shell->envp[i][len] == '=')
			return (&shell->envp[i][len + 1]);
		i++;
	}
	return (NULL);
}

static void	update_env_variable(t_shell *shell, char *key, char *new_value)
{
	int		i;
	int		len;
	char	*new_entry;

	len = ft_strlen(key);
	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], key, len) == 0 &&
			shell->envp[i][len] == '=')
		{
			new_entry = ft_strjoin(key, "=");
			if (!new_entry)
				return;
			free(shell->envp[i]);
			shell->envp[i] = ft_strjoin(new_entry, new_value);
			free(new_entry);
			return ;
		}
		i++;
	}
}

int	ft_cd(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("getcwd");
		return (1);
	}
	if (!cmd->argv[1])
	{
		path = get_key_value("HOME", shell);
		if (!path)
		{
			printf("cd: HOME not set");
			free(oldpwd);
			return (1);
		}
	}
	else if (ft_strncmp(cmd->argv[1], "-", 1) == 0)
	{
		path = get_key_value("OLDPWD", shell);
		if (!path)
		{
			printf("cd: OLDPWD not set");
			free(oldpwd);
			return (1);
		}
		printf("%s\n", path);
	}
	else
	{
		path = cmd->argv[1];
	}
	update_env_variable(shell, "OLDPWD", oldpwd);
	free(oldpwd);
	if (chdir(path) != 0)
	{
		perror("chdir");
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("getcwd");
		return (1);
	}
	update_env_variable(shell, "PWD", pwd);
	free(pwd);
	return (0);
}
*/

int	ft_cd(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	path = NULL;
	ft_change_oldpwd_env(shell);
	if (cmd->argc > 1)
		path = ft_strdup(cmd->argv[1]);
	else
	{
		path = ft_get_env_value("HOME", shell);
		if (!path)
		{
			cmd->error_message = ft_strdup("cd: HOME not set");
			return (1);
		}
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		free(path);
		return (1);
	}
	ft_change_pwd_env(shell);
	//free(path);
	return (0);
}

void	ft_change_oldpwd_env(t_shell *shell)
{
	char	*oldpwd;
	char	*new_oldpwd;
	int		i;

	oldpwd = NULL;
	new_oldpwd = NULL;
	i = 0;
	oldpwd = ft_get_env_value("PWD", shell);
	if (!oldpwd)
		return;
	new_oldpwd = ft_strjoin("OLDPWD=", oldpwd);
	if (!new_oldpwd)
	{
		perror("malloc");
		return;
	}
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], "OLDPWD=", 7) == 0)
		{
			free(shell->envp[i]);
			shell->envp[i] = new_oldpwd;
			return;
		}
		i++;
	}
	shell->envp = ft_add_to_env(shell->envp, new_oldpwd);
	free(new_oldpwd);
}

void	ft_change_pwd_env(t_shell *shell)
{
	char	*cwd;
	char	*new_pwd;
	int		i;

	new_pwd = NULL;
	i = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		return;
	}
	new_pwd = ft_strjoin("PWD=", cwd);
	if (!new_pwd)
	{
		perror("malloc");
		return;
	}
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], "PWD=", 4) == 0)
		{
			free(shell->envp[i]);
			shell->envp[i] = new_pwd;
			return;
		}
		i++;
	}
	shell->envp = ft_add_to_env(shell->envp, new_pwd);
	free(new_pwd);
}
char	*ft_get_env_value(const char *key, t_shell *shell)
{
	int		i;
	int		len;

	i = 0;
	if (!key || !shell || !shell->envp)
		return (NULL);
	len = ft_strlen(key);
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], key, len) == 0 &&
			shell->envp[i][len] == '=')
			return (shell->envp[i] + len + 1);
		i++;
	}
	return (NULL);
}
char	**ft_add_to_env(char **envp, const char *new_var)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (envp[i])
		i++;
	new_envp = (char **)malloc((i + 2) * sizeof(char *));
	if (!new_envp)
	{
		perror("malloc");
		return (envp);
	}
	i = 0;
	while (envp[i])
	{
		new_envp[i] = envp[i];
		i++;
	}
	new_envp[i] = ft_strdup(new_var);
	new_envp[i + 1] = NULL;
	free(envp);
	return (new_envp);
}
