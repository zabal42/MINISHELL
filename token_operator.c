/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:37:21 by jesssanc          #+#    #+#             */
/*   Updated: 2025/06/02 10:40:13 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_double_operator(const char *line, size_t *i,
	t_token **tokens)
{
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		add_token(tokens, new_token(T_HEREDOC, substr_dup("<<", 2), Q_NONE));
		(*i) += 2;
		return (1);
	}
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		add_token(tokens, new_token(T_REDIR_APPEND, substr_dup(">>", 2),
				Q_NONE));
		(*i) += 2;
		return (1);
	}
	return (0);
}

int	handle_single_operator(const char *line, size_t *i,
		t_token **tokens)
{
	if (line[*i] == '<')
	{
		add_token(tokens, new_token(T_REDIR_IN, substr_dup("<", 1), Q_NONE));
		(*i)++;
		return (1);
	}
	else if (line[*i] == '>')
	{
		add_token(tokens, new_token(T_REDIR_OUT, substr_dup(">", 1), Q_NONE));
		(*i)++;
		return (1);
	}
	return (0);
}

int	handle_pipe_operator(const char *line, size_t *i, t_token **tokens)
{
	if (line[*i] == '|')
	{
		add_token(tokens, new_token(T_PIPE, substr_dup("|", 1), Q_NONE));
		(*i)++;
		return (1);
	}
	return (0);
}

int	handle_operator(const char *line, size_t *i, t_token **tokens)
{
	if (handle_pipe_operator(line, i, tokens))
		return (1);
	if (handle_double_operator(line, i, tokens))
		return (1);
	if (handle_single_operator(line, i, tokens))
		return (1);
	return (0);
}
