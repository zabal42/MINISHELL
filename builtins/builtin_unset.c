/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:49:00 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/16 10:51:36 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_shell *shell, t_cmd *cmd)
{
	int	i;

	if (cmd->argc <= 1)
		return (0);
	i = 1;
	while (cmd->argv[i])
	{
		if (!ft_is_valid_identifier(cmd->argv[i]))
		{
			printf("unset: `%s': not a valid identifier\n", cmd->argv[i]);
			shell->exit_status = 1;
		}
		else
		{
			ft_remove_from_env(shell, cmd->argv[i]);
			shell->exit_status = 0;
		}
		i++;
	}
	return (shell->exit_status);
}

void	ft_remove_from_env(t_shell *shell, const char *key)
{
	int i;
	int j;
	int key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], key, key_len) == 0 &&
			shell->envp[i][key_len] == '=')
		{
			free(shell->envp[i]);
			j = i;
			while (shell->envp[j])
			{
				shell->envp[j] = shell->envp[j + 1];
				j++;
			}
			return ;
		}
		i++;
	}
}
