/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabal-m <mzabal-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:59:16 by mzabal-m          #+#    #+#             */
/*   Updated: 2025/05/12 12:04:01 by mzabal-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "parser.h"
#include "libft/inc/libft.h"


static t_token	*new_token(t_token_type type, char *val)
{
	t_token *tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->value = val;
	tok->next = NULL;
	return (tok);
}

static void	add_token(t_token **head, t_token *new)
{
	t_token *tmp = *head;
	if (!tmp)
		*head = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static char	*substr_dup(const char *start, size_t len)
{
	char *str = malloc(len + 1);
	if (!str)
		return (NULL);
	strncpy(str, start, len);
	str[len] = '\0';
	return (str);
}

t_token	*tokenize_input(const char *line)
{
	t_token *tokens = NULL;
	size_t i = 0;

	while (line[i])
	{
		if (is_space(line[i]))
			i++;
		else if (line[i] == '|')
		{
			add_token(&tokens, new_token(T_PIPE, substr_dup("|", 1)));
			i++;
		}
		else if (line[i] == '<' && line[i + 1] == '<')
		{
			add_token(&tokens, new_token(T_HEREDOC, substr_dup("<<", 2)));
			i += 2;
		}
		else if (line[i] == '>' && line[i + 1] == '>')
		{
			add_token(&tokens, new_token(T_REDIR_APPEND, substr_dup(">>", 2)));
			i += 2;
		}
		else if (line[i] == '<')
		{
			add_token(&tokens, new_token(T_REDIR_IN, substr_dup("<", 1)));
			i++;
		}
		else if (line[i] == '>')
		{
			add_token(&tokens, new_token(T_REDIR_OUT, substr_dup(">", 1)));
			i++;
		}
		else
		{
			size_t start = i;
			while (line[i] && !is_space(line[i]) && !strchr("|<>", line[i]))
				i++;
			add_token(&tokens, new_token(T_WORD, substr_dup(&line[start], i - start)));
		}
	}
	return tokens;
}
