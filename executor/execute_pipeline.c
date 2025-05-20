/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:25:32 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/20 11:33:49 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_pipeline(t_cmd *cmds, t_shell *shell)
{
	int		pipefd[2];
	int		in_fd;
	int		status;
	pid_t	pid;
	t_cmd	*cmd;
	int		last_pid;

	last_pid = -1;
	cmd = cmds;
	in_fd = STDIN_FILENO;
	while (cmd)
	{
		if (cmd->next)
			pipe(pipefd);
		pid = fork();
		if (pid == 0)
		{
			if (in_fd != STDIN_FILENO)
			{
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}
			if (cmd->next)
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
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		if (cmd->next)
		{
			close(pipefd[1]);
			in_fd = pipefd[0];
		}
		last_pid = pid;
		cmd = cmd->next;
	}
	while (wait(&status) > 0); // Espera a todos los hijos
	return (WEXITSTATUS(status));
}
