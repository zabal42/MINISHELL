/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelzabal <mikelzabal@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:19:35 by mikelzabal        #+#    #+#             */
/*   Updated: 2025/05/20 12:06:17 by mikelzabal       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"
#include "libft.h"

/*
** free_redirections:
** Libera toda la lista de redirecciones de un comando.
*/
void	free_redirections(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		free(tmp->target);
		free(tmp);
	}
}

/*
** free_cmds:
** Libera completamente la lista de comandos t_cmd,
** incluyendo argv, redirections y mensaje de error.
*/
void	free_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->argv)
		{
			i = 0;
			while (tmp->argv[i])
				free(tmp->argv[i++]);
			free(tmp->argv);
		}
		if (tmp->error_message)
			free(tmp->error_message);
		if (tmp->redirections)
			free_redirections(tmp->redirections);
		free(tmp);
	}
}
