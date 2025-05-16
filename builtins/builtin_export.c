/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:35:20 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/16 10:41:22 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export(t_shell *shell, t_cmd *cmd)
{
	int i;

	i = 0;
	if (cmd->argc == 1)
	{
		while (shell->envp[i])
		{
			printf("declare -x %s\n", shell->envp[i]);
			i++;
		}
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
	int		i;
	char	*key;
	char	*value;
	char	*new_entry;
	size_t	key_len;

	key_len = 0;
	while (var_with_value[key_len] && var_with_value[key_len] != '=')
		key_len++;
	key = malloc(key_len + 1);
	if (!key)
		return;
	ft_strlcpy(key, var_with_value, key_len + 1);
	value = ft_strdup(&var_with_value[key_len + 1]);
	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], key, key_len) == 0 &&
			shell->envp[i][key_len] == '=')
		{
			new_entry = ft_strjoin(key, "=");
			if (!new_entry)
			{
				free(key);
				free(value);
				return;
			}
			new_entry = ft_strjoin(new_entry, value);
			free(shell->envp[i]);
			shell->envp[i] = new_entry;
			free(key);
			free(value);
			return;
		}
		i++;
	}
	new_entry = ft_strjoin(key, "=");
	if (!new_entry)
	{
		free(key);
		free(value);
		return;
	}
	new_entry = ft_strjoin(new_entry, value);
	shell->envp = ft_realloc_env(shell->envp, new_entry);
	free(key);
	free(value);
}

char	**ft_realloc_env(char **envp, const char *new_entry)
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
		new_envp[i] = envp[i];
		i++;
	}
	new_envp[i] = ft_strdup(new_entry);
	new_envp[i + 1] = NULL;
	free(envp);
	return (new_envp);
}
