/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:20:11 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/14 12:10:17 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int execute_command(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	if (ft_strncmp(cmd->argv[0], "pwd", 3) == 0)
		return (ft_pwd(shell));
	if (ft_strncmp(cmd->argv[0], "echo", 4) == 0)
		return (ft_echo(cmd));
	if (ft_strncmp(cmd->argv[0], "cd", 2) == 0)
		return (ft_cd(shell, cmd));
	if (!(access(cmd->argv[0], X_OK) == 0))
	{
		cmd->argv[0] = find_executable(cmd->argv[0], shell->envp);
		if (!cmd->argv[0])
		{
			printf("minishell: %s: command not found\n", cmd->argv[0]);
			shell->exit_status = 127;
			return (shell->exit_status);
		}
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error al crear el proceso hijo");
		return (shell->exit_status);
	}
	if (pid == 0)
	{
		if (execve(cmd->argv[0], cmd->argv, shell->envp) == -1)
		{
			perror("Error al ejecutar el comando");
			exit(127);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (status == 0)
			shell->exit_status = 0;
		else if (status == 127)
			shell->exit_status = 127;
		else
			shell->exit_status = 1;
	}
	return (shell->exit_status);
}
