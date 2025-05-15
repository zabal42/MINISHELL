/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:35:20 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/15 12:04:46 by jesssanc         ###   ########.fr       */
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
