/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:20:11 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/27 12:27:58 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	if_is_builtin(t_cmd *cmd, t_shell *shell)
{
	int		stdin_copy;
	int		stdout_copy;
	int		status;

	status = 0;
	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	if (open_redirections(cmd) < 0)
	{
		dup2(stdin_copy, STDIN_FILENO);
		dup2(stdout_copy, STDOUT_FILENO);
		close(stdin_copy);
		close(stdout_copy);
		return (1);
	}
	status = exec_builtin(cmd, shell);
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
	return (status);
}

int	execute_command(t_cmd *cmd, t_shell *shell)
{
	int		status;
	pid_t	pid;

	status = 0;
	if (cmd->is_builtin)
		return (if_is_builtin(cmd, shell));
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (open_redirections(cmd) < 0)
			exit(1);
		execve(cmd->full_path, cmd->argv, shell->envp);
		perror("execve");
		exit(127);
	}
	else if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &status, 0);
		setup_signals();
		return (WEXITSTATUS(status));
	}
	else
	{
		perror("fork");
		return (1);
	}
}
