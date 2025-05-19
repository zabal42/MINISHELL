/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelzabal <mikelzabal@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:54:52 by mikelzabal        #+#    #+#             */
/*   Updated: 2025/05/19 13:39:34 by mikelzabal       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parser.h"

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

/*
** add_word_to_cmd:
** Añade una palabra (argumento) al array argv del comando actual.
** Incrementa argc y asegura que argv termina en NULL.
*/
void	add_word_to_cmd(t_cmd *cmd, char *word)
{
	char	**new_argv;
	int		i;

	new_argv = malloc(sizeof(char *) * (cmd->argc + 2));
	if (!new_argv)
		return ;
	i = 0;
	while (i < cmd->argc)
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[i++] = ft_strdup(word);
	new_argv[i] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
	cmd->argc++;
}

/*
** parse_tokens:
** Función principal del parser.
** Convierte la lista de tokens en una lista de estructuras t_cmd,
** separando los comandos por pipes y agrupando argumentos/redirecciones.
*/
t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmds = NULL;
	t_cmd	*current = NULL;

	while (tokens)
	{
		if (!current)
		{
			current = init_cmd();
			if (!current)
				return (NULL);
			add_cmd_to_list(&cmds, current);
		}
		if (tokens->type == T_PIPE)
		{
			current = NULL;
			tokens = tokens->next;
			continue;
		}
		else if (tokens->type == T_WORD)
		{
			add_word_to_cmd(current, tokens->value);
			tokens = tokens->next; // ✅ AVANZAS AL SIGUIENTE TOKEN
		}
		else if (tokens->type == T_REDIR_IN || tokens->type == T_REDIR_OUT
				|| tokens->type == T_REDIR_APPEND || tokens->type == T_HEREDOC)
		{
			handle_redirection(current, &tokens);
			continue;
		}
		
	}
	return (cmds);
}
/*
** handle_redirection:
** Procesa una redirección y la añade a la lista de redirecciones del comando.
** Avanza el puntero de token para saltar el archivo objetivo.
*/
void	handle_redirection(t_cmd *cmd, t_token **tokens)
{
	t_token	*redir = *tokens;
	t_token	*target = redir->next;
	t_redir	*new;

	if (!target || target->type != T_WORD)
	{
		cmd->error_message = ft_strdup("syntax error near unexpected token");
		return ;
	}
	new = malloc(sizeof(t_redir));
	if (!new)
		return ;
	new->target = ft_strdup(target->value);
	new->next = NULL;

	if (redir->type == T_REDIR_IN)
		new->type = REDIR_IN;
	else if (redir->type == T_REDIR_OUT)
		new->type = REDIR_OUT;
	else if (redir->type == T_REDIR_APPEND)
		new->type = REDIR_APPEND;
	else if (redir->type == T_HEREDOC)
		new->type = REDIR_HEREDOC;
	add_redir_to_list(&cmd->redirections, new);
	*tokens = target -> next; // avanzamos
}
/*
** add_redir_to_list:
** Añade una redirección a la lista enlazada dentro de un t_cmd.
*/
void	add_redir_to_list(t_redir **head, t_redir *new)
{
	t_redir	*tmp;

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
