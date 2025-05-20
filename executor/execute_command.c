/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:20:11 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/20 11:26:39 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_command(t_cmd *cmd, t_shell *shell)
{
	int		status;
	pid_t	pid;
	int		stdin_copy;
	int		stdout_copy;

	status = 0;
	if (cmd->is_builtin)
	{
		stdin_copy = dup(STDIN_FILENO); // o 0
		stdout_copy = dup(STDOUT_FILENO); // o 1
		if (open_redirections(cmd) < 0)
		{
			dup2(stdin_copy, STDIN_FILENO);
			dup2(stdout_copy, STDOUT_FILENO);
			close(stdin_copy);
			close(stdout_copy);
			return (1);
		}
		status = exec_builtin(cmd, shell); // devuelve 0 si ejec correcta, 1 si error y 127 comand not found
		dup2(stdin_copy, STDIN_FILENO);
		dup2(stdout_copy, STDOUT_FILENO);
		close(stdin_copy);
		close(stdout_copy);
		return (status);
	}
	pid = fork();
	if (pid == 0)
	{
		if (open_redirections(cmd) < 0)
			exit(1);
		execve(cmd->full_path, cmd->argv, shell->envp);
		perror("execve");
		exit(127);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	else
	{
		perror("fork");
		return (1);
	}
}
