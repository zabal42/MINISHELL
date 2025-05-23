/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelzabal <mikelzabal@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:25:32 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/23 18:08:53 by mikelzabal       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	child_process(t_cmd *cmd, t_shell *shell, int in_fd, int *pipefd)
{
	if (in_fd != STDIN_FILENO) // si no es el primer comando
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (cmd->next) // si no es el último comando
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	open_redirections(cmd);
	if (cmd->is_builtin)
		exit(exec_builtin(cmd, shell)); // Ejecuta builtin en el hijo
	else
		execve(cmd->full_path, cmd->argv, shell->envp);
	perror("execve");
	exit(127);
}

static int	parent_process(int *in_fd, int *pipefd, t_cmd *cmd, pid_t pid)
{
	int	last_pid;

	last_pid = -1;
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	if (cmd->next)
	{
		close(pipefd[1]);
		*in_fd = pipefd[0];
	}
	last_pid = pid;
	return (last_pid);
}

int	execute_pipeline(t_cmd *cmds, t_shell *shell)
{
	int		pipefd[2];
	int		in_fd;
	int		status;
	pid_t	pid;
	t_cmd	*cmd;

	cmd = cmds;
	in_fd = STDIN_FILENO;
	status = 0;
	while (cmd)
	{
		if (cmd->next)
			pipe(pipefd);
		if (cmd->is_builtin && !cmd->next && in_fd == STDIN_FILENO)
		{
		// Ejecutar el builtin en el padre si es único comando y no hay pipe
			shell->exit_status = exec_builtin(cmd, shell);
			return (shell->exit_status);
		}
		pid = fork();
		if (pid == 0)
			child_process(cmd, shell, in_fd, pipefd);
		else
			parent_process(&in_fd, pipefd, cmd, pid);
		cmd = cmd->next;
	}
	while (wait(&status) > 0) // Espera a todos los hijos
		continue ;
	return (WEXITSTATUS(status));
}
