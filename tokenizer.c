/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelzabal <mikelzabal@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:59:16 by mzabal-m          #+#    #+#             */
/*   Updated: 2025/05/31 12:41:04 by mikelzabal       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "parser.h"
#include "libft/inc/libft.h"

static t_token	*new_token(t_token_type type, char *val, t_quote_type quote)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->value = val;
	tok->quote = quote;
	tok->next = NULL;
	return (tok);
}

static void	add_token(t_token **head, t_token *new)
{
	t_token	*tmp;

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

static char	*substr_dup(const char *start, size_t len)
{
	char	*str;

	str = malloc(len + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, start, len);
	str[len] = '\0';
	return (str);
}

static int	handle_double_operator(const char *line, size_t *i,
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

static int	handle_single_operator(const char *line, size_t *i,
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

static int	handle_pipe_operator(const char *line, size_t *i, t_token **tokens)
{
	if (line[*i] == '|')
	{
		add_token(tokens, new_token(T_PIPE, substr_dup("|", 1), Q_NONE));
		(*i)++;
		return (1);
	}
	return (0);
}

static int	handle_operator(const char *line, size_t *i, t_token **tokens)
{
	if (handle_pipe_operator(line, i, tokens))
		return (1);
	if (handle_double_operator(line, i, tokens))
		return (1);
	if (handle_single_operator(line, i, tokens))
		return (1);
	return (0);
}

static int	handle_quoted_segment(const char *line, size_t *i, t_token **tokens)
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

static void	handle_word_segment(const char *line, size_t *i, t_token **tokens)
{
	size_t	start;

	start = *i;
	while (line[*i] && !is_space(line[*i])
		&& !is_metachar(line[*i]) && !is_quote(line[*i]))
		(*i)++;
	add_token(tokens, new_token(T_WORD, substr_dup(&line[start], *i - start),
			Q_NONE));
}

static t_token	*tokenize_loop(const char *line, t_token **tokens)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (is_space(line[i]))
			i++;
		else if (handle_operator(line, &i, tokens))
			;
		else if (is_quote(line[i]))
		{
			if (!handle_quoted_segment(line, &i, tokens))
				return (NULL);
		}
		else
			handle_word_segment(line, &i, tokens);
	}
	return (*tokens);
}

t_token	*tokenize_input(const char *line)
{
	t_token	*tokens;
	t_token	*result;

	tokens = NULL;
	result = tokenize_loop(line, &tokens);
	return (result);
}
