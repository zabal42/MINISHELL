/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelzabal <mikelzabal@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:41:29 by mikelzabal        #+#    #+#             */
/*   Updated: 2025/05/23 10:33:39 by mikelzabal       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parser.h"

/*
** parse_tokens:
** Función principal del parser.
** Convierte la lista de tokens en una lista de estructuras t_cmd,
** separando los comandos por pipes y agrupando argumentos/redirecciones.
*/

static t_cmd	*start_new_cmd(t_cmd **cmds)
{
	t_cmd *new = init_cmd();
	if (!new)
		return (NULL);
	add_cmd_to_list(cmds, new);
	return (new);
}

static void	handle_token(t_token **tokens, t_cmd **current, t_shell *shell)
{
	t_token *tok = *tokens;

	if (tok->type == T_PIPE)
		*current = NULL;
	else if (tok->type == T_WORD)
		add_word_to_cmd(*current, (*tokens)->value, shell, (*tokens)->quote);
	else if (tok->type == T_REDIR_IN || tok->type == T_REDIR_OUT
		|| tok->type == T_REDIR_APPEND || tok->type == T_HEREDOC)
	{
		handle_redirection(*current, tokens, shell);
		return ; // ya avanza dentro de handle_redirection
	}
	*tokens = tok->next;
}

t_cmd	*parse_tokens(t_token *tokens, t_shell *shell)
{
	t_cmd	*cmds = NULL;
	t_cmd	*current = NULL;

	while (tokens)
	{
		if (!current)
		{
			current = start_new_cmd(&cmds);
			if (!current)
				return (NULL);
		}
		handle_token(&tokens, &current, shell);
	}
	return (cmds);
}
