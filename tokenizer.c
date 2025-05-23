/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelzabal <mikelzabal@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:59:16 by mzabal-m          #+#    #+#             */
/*   Updated: 2025/05/23 10:27:44 by mikelzabal       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "parser.h"
#include "libft/inc/libft.h"

static t_token *new_token(t_token_type type, char *val, t_quote_type quote)
{
	t_token *tok = malloc(sizeof(t_token));
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

t_token	*tokenize_input(const char *line)
{
	t_token	*tokens = NULL;
	size_t	i = 0;
	size_t	start;
	t_token	*new;
	char	*quoted;
	t_quote_type	qtype;

	while (line[i])
	{
		if (is_space(line[i]))
			i++;
		else if (line[i] == '|')
			add_token(&tokens, new_token(T_PIPE, substr_dup("|", 1), Q_NONE)), i++;
		else if (line[i] == '<' && line[i + 1] == '<')
			add_token(&tokens, new_token(T_HEREDOC, substr_dup("<<", 2), Q_NONE)), i += 2;
		else if (line[i] == '>' && line[i + 1] == '>')
			add_token(&tokens, new_token(T_REDIR_APPEND, substr_dup(">>", 2), Q_NONE)), i += 2;
		else if (line[i] == '<')
			add_token(&tokens, new_token(T_REDIR_IN, substr_dup("<", 1), Q_NONE)), i++;
		else if (line[i] == '>')
			add_token(&tokens, new_token(T_REDIR_OUT, substr_dup(">", 1), Q_NONE)), i++;
		else if (is_quote(line[i]))
		{
			if (!check_closing_quote(&line[i]))
			{
				ft_putendl_fd("syntax error: unclosed quote", 2);
				free_tokens(tokens);
				return (NULL);
			}
			qtype = (line[i] == '\'') ? Q_SINGLE : Q_DOUBLE;
			quoted = concat_quoted_segments(line, &i);
			if (!quoted)
				return (free_tokens(tokens), NULL);
			new = new_token(T_WORD, quoted, qtype);
			add_token(&tokens, new);
		}
		else
		{
			start = i;
			while (line[i] && !is_space(line[i])
				&& !is_metachar(line[i]) && !is_quote(line[i]))
				i++;
			add_token(&tokens, new_token(T_WORD, substr_dup(&line[start], i - start), Q_NONE));
		}
	}
	return (tokens);
}
