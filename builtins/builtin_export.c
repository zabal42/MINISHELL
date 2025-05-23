/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelzabal <mikelzabal@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:35:20 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/23 14:01:35 by mikelzabal       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_find_existing_var(t_shell *shell, char *key, char *value,
	size_t key_len)
{
	int		i;
	char	*new_entry;
	char	*temp;

	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], key, key_len) == 0
			&& (shell->envp[i][key_len] == '=' || !shell->envp[i][key_len]))
		{
			new_entry = ft_strjoin(key, "=");
			if (!new_entry)
				return (0);
			temp = new_entry;
			new_entry = ft_strjoin(new_entry, value);
			free(temp);
			if (!new_entry)
				return (0);
			free(shell->envp[i]);
			shell->envp[i] = new_entry;
			return (1);
		}
		i++;
	}
	return (0);
}

static void	ft_add_new_var(t_shell *shell, char *key, char *value)
{
	char	*new_entry;
	char	*temp;

	new_entry = ft_strjoin(key, "=");
	if (!new_entry)
		return ;
	temp = new_entry;
	new_entry = ft_strjoin(new_entry, value);
	free(temp);
	if (!new_entry)
		return ;

	// 💥 CLAVE: esto es lo que te faltaba
	shell->envp = ft_realloc_env(shell->envp, new_entry);

	free(new_entry);
}
/*
int	ft_export(t_shell *shell, t_cmd *cmd)
{
	int	i;

	if (!cmd->argv[1])
	{
		i = 0;
		while (shell->envp[i])
			printf("declare -x %s\n", shell->envp[i++]);
		return (0);
	}
	i = 1;
	while (cmd->argv[i])
	{
		if (!ft_is_valid_identifier(cmd->argv[i]))
		{
			printf("export: `%s': not a valid identifier\n", cmd->argv[i]);
			shell->exit_status = 1;
		}
		else
		{
			ft_add_or_update_env(shell, cmd->argv[i]);
			shell->exit_status = 0;
		}
		i++;
	}
	return (shell->exit_status);
}
	*/
int	ft_export(t_shell *shell, t_cmd *cmd)
{
	int	i;

	if (!cmd->argv[1])
	{
		i = 0;
		while (shell->envp[i])
		{
			if (ft_strchr(shell->envp[i], '='))
				printf("declare -x %s\n", shell->envp[i]);
			else
				printf("declare -x %s\n", shell->envp[i]);
			i++;
		}
		shell->exit_status = 0;
		return (0);
	}

	i = 1;
	while (cmd->argv[i])
	{
		if (!ft_is_valid_identifier(cmd->argv[i]))
		{
			printf("export: `%s': not a valid identifier\n", cmd->argv[i]);
			shell->exit_status = 1;
		}
		else
		{
			ft_add_or_update_env(shell, cmd->argv[i]);
			shell->exit_status = 0;
		}
		i++;
	}
	return (shell->exit_status);
}

void	ft_add_or_update_env(t_shell *shell, const char *var_with_value)
{
	int		found;
	char	*key;
	char	*value;
	size_t	key_len;

	key_len = 0;
	while (var_with_value[key_len] && var_with_value[key_len] != '=')
		key_len++;
	key = malloc(key_len + 1);
	if (!key)
		return ;
	ft_strlcpy(key, var_with_value, key_len + 1);
	if (var_with_value[key_len] == '=')
		value = ft_strdup(&var_with_value[key_len + 1]);
	else
		value = ft_strdup("");

	found = ft_find_existing_var(shell, key, value, key_len);
	if (!found)
		ft_add_new_var(shell, key, value); // 🔥 aquí debe asignar a shell->envp

	free(key);
	free(value);
}

char **ft_realloc_env(char **envp, const char *new_entry)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc((i + 2) * sizeof(char *));
	if (!new_envp)
		return (envp);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = ft_strdup(new_entry);
	new_envp[i + 1] = NULL;

	// ❌ No hagas free(envp) aquí, libéralo en ft_cleanup_shell
	return (new_envp);
}
