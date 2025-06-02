/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_classify.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:24:25 by jesssanc          #+#    #+#             */
/*   Updated: 2025/06/02 10:40:56 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quoted_segment(const char *line, size_t *i, t_token **tokens)
{
	t_quote_type	qtype;
	char			*quoted;
	t_token			*new;

	if (!check_closing_quote(&line[*i]))
	{
		ft_putendl_fd("syntax error: unclosed quote", 2);
		free_tokens(*tokens);
		return (0);
	}
	if (line[*i] == '\'')
		qtype = Q_SINGLE;
	else
		qtype = Q_DOUBLE;
	quoted = concat_quoted_segments(line, i);
	if (!quoted)
	{
		free_tokens(*tokens);
		return (0);
	}
	new = new_token(T_WORD, quoted, qtype);
	add_token(tokens, new);
	return (1);
}

void	handle_word_segment(const char *line, size_t *i, t_token **tokens)
{
	size_t	start;

	start = *i;
	while (line[*i] && !is_space(line[*i])
		&& !is_metachar(line[*i]) && !is_quote(line[*i]))
		(*i)++;
	add_token(tokens, new_token(T_WORD, substr_dup(&line[start], *i - start),
			Q_NONE));
}
