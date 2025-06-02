/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:02:52 by jesssanc          #+#    #+#             */
/*   Updated: 2025/06/02 11:05:07 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** init_cmd:
** Crea e inicializa una estructura t_cmd vacía con valores por defecto.
** Devolverá un nuevo comando con campos preparados para rellenar.
*/
t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->argc = 0;
	cmd->full_path = NULL;
	cmd->is_builtin = 0;
	cmd->background = 0;
	cmd->input_fd = -1;
	cmd->output_fd = -1;
	cmd->error_message = NULL;
	cmd->redirections = NULL;
	cmd->next = NULL;
	return (cmd);
}

/*
** add_cmd_to_list:
** Añade un nuevo comando (t_cmd) a una lista enlazada de comandos.
** Útil cuando encontramos un pipe y se inicia una nueva estructura.
*/
void	add_cmd_to_list(t_cmd **head, t_cmd *new)
{
	t_cmd	*tmp;

	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
