/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelzabal <mikelzabal@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:21:30 by mikelzabal        #+#    #+#             */
/*   Updated: 2025/05/20 12:08:02 by mikelzabal       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser.h"
#include "libft.h"

/*
** print_redirections:
** Imprime la lista de redirecciones de un comando.
*/
void	print_redirections(t_redir *redir)
{
	while (redir)
	{
		printf("  Redir: ");
		if (redir->type == REDIR_IN)
			printf("<");
		else if (redir->type == REDIR_OUT)
			printf(">");
		else if (redir->type == REDIR_APPEND)
			printf(">>");
		else if (redir->type == REDIR_HEREDOC)
			printf("<<");
		printf(" %s\n", redir->target);
		redir = redir->next;
	}
}

/*
** print_cmds:
** Imprime todos los comandos con sus argumentos, redirecciones y errores.
*/
void	print_cmds(t_cmd *cmd)
{
	int	i;
	int	index;

	index = 0;
	if (!cmd)
	{
		printf("⚠️  No hay comandos para imprimir.\n");
		return ;
	}
	while (cmd)
	{
		printf("=== Comando %d ===\n", index++);
		i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			printf("  Arg: %s\n", cmd->argv[i]);
			i++;
		}
		if (cmd->redirections)
			print_redirections(cmd->redirections);
		if (cmd->error_message)
			printf("  Error: %s\n", cmd->error_message);
		cmd = cmd->next;
	}
}
