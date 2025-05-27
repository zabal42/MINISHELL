/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelzabal <mikelzabal@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:12:02 by mikelzabal        #+#    #+#             */
/*   Updated: 2025/05/27 11:16:39 by mikelzabal       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelzabal <mikelzabal@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:30:00 by mikelzabal        #+#    #+#             */
/*   Updated: 2025/05/23 12:30:00 by mikelzabal       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

static int	syntax_error(const char *near)
{
	printf("minishell: syntax error near unexpected token `%s'\n", near);
	return (0);
}

static int	is_redirection(t_token *t)
{
	return (t->type == T_REDIR_IN || t->type == T_REDIR_OUT
		|| t->type == T_REDIR_APPEND || t->type == T_HEREDOC);
}

int	validate_tokens(t_token *tok)
{
	if (!tok)
		return (1);
	if (tok->type == T_PIPE || is_redirection(tok))
		return (syntax_error(tok->value));
	while (tok && tok->next)
	{
		if (tok->type == T_PIPE && tok->next->type == T_PIPE)
			return (syntax_error(tok->next->value));
		if (is_redirection(tok) && (tok->next->type != T_WORD))
			return (syntax_error(tok->next->value));
		if (is_redirection(tok) && is_redirection(tok->next))
			return (syntax_error(tok->next->value));
		tok = tok->next;
	}
	if (tok && (tok->type == T_PIPE || is_redirection(tok)))
		return (syntax_error("newline"));
	return (1);
}
