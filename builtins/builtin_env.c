/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:00:15 by jesssanc          #+#    #+#             */
/*   Updated: 2025/06/02 09:40:27 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_shell *shell, t_cmd *cmd)
{
	int	i;

	if (cmd->argc > 1)
	{
		printf("env: no arguments are allowed\n");
		shell->exit_status = 1;
		return (shell->exit_status = 1);
	}
	i = 0;
	while (shell->envp[i])
	{
		if (ft_strchr(shell->envp[i], '='))
			printf("%s\n", shell->envp[i]);
		i++;
	}
	shell->exit_status = 0;
	return (shell->exit_status = 0);
}
