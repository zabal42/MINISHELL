/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:48:04 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/15 12:10:39 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_key_value(char *key, t_shell *shell)
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

void	update_env_variable(t_shell *shell, char *key, char *new_value)
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
			shell->envp[i] = ft_strjoin(new_entry, new_value);
			free(new_entry);
			return ;
		}
		i++;
	}
}

int	ft_is_valid_identifier(const char *str)
{
	int i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
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

