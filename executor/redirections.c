/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessica <jessica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:28:46 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/29 19:21:59 by jessica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	redir_in(t_redir *redir)
{
	int	fd;

	fd = open(redir->target, O_RDONLY);
	if (fd < 0)
	{
		perror(redir->target);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	redir_out(t_redir *redir)
{
	int	fd;

	fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(redir->target);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	redir_append(t_redir *redir)
{
	int	fd;

	fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(redir->target);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
/*
static int	redir_heredoc(t_redir *redir)
{
	int	fd;

	fd = handle_heredoc(redir->target);
	if (fd < 0)
	{
		perror("heredoc");
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}
*/
static int redir_heredoc(t_redir *redir) {
	if (redir->fd < 0)
		return (-1);
	dup2(redir->fd, STDIN_FILENO);
	close(redir->fd);
	return (0);
}

int	open_redirections(t_cmd *cmd)
{
	t_redir	*redir;
	int		result;

	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == REDIR_IN)
			result = redir_in(redir);
		else if (redir->type == REDIR_OUT)
			result = redir_out(redir);
		else if (redir->type == REDIR_APPEND)
			result = redir_append(redir);
		else if (redir->type == REDIR_HEREDOC)
			result = redir_heredoc(redir);
		if (result < 0)
			return (-1);
		redir = redir->next;
	}
	return (0);
}
