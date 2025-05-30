/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessica <jessica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:40:11 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/30 20:20:45 by jessica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	run_heredoc_loop(const char *delim, int write_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(1, "\n", 1);
			close(write_fd);
			exit(130);
		}
		if (ft_strlen(line) == ft_strlen(delim)
			&& ft_strncmp(line, delim, ft_strlen(delim)) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
	exit(0);
}

int	preprocess_heredocs(t_cmd *cmds)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redirections;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
			{
				redir->fd = handle_heredoc(redir->target);
				if (redir->fd < 0)
				{
					perror("heredoc");
					return (1);
				}
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	handle_heredoc(const char *delim)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (close(pipefd[0]), close(pipefd[1]), (-1));
	if (pid == 0)
	{
		restore_signals();
		close(pipefd[0]);
		run_heredoc_loop(delim, pipefd[1]);
	}
	ignore_signals();
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return (close(pipefd[0]), (-1));
	return (pipefd[0]);
}
