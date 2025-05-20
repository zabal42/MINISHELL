/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:22:26 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/20 11:28:00 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!cmd->argv || !cmd->argv[0])
		return (1);
	if (ft_strncmp(cmd->argv[0], "pwd", 3) == 0)
		return (ft_pwd(shell));
	else if (ft_strncmp(cmd->argv[0], "echo", 4) == 0)
		return (ft_echo(cmd));
	else if (ft_strncmp(cmd->argv[0], "cd", 2) == 0)
		return (ft_cd(shell, cmd));
	else if (ft_strncmp(cmd->argv[0], "export", 6) == 0)
		return (ft_export(shell, cmd));
	else if (ft_strncmp(cmd->argv[0], "unset", 5) == 0)
		return (ft_unset(shell, cmd));
	else if (ft_strncmp(cmd->argv[0], "env", 3) == 0)
		return (ft_env(shell, cmd));
	else if (ft_strncmp(cmd->argv[0], "exit", 4) == 0)
		return (ft_exit(shell, cmd));
	return (127);
}
