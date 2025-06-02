/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:59:16 by mzabal-m          #+#    #+#             */
/*   Updated: 2025/06/02 10:41:43 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "parser.h"
#include "libft/inc/libft.h"

t_token	*new_token(t_token_type type, char *val, t_quote_type quote)
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

void	add_token(t_token **head, t_token *new)
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

char	*substr_dup(const char *start, size_t len)
{
	char	*str;

	str = malloc(len + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, start, len);
	str[len] = '\0';
	return (str);
}

t_token	*tokenize_loop(const char *line, t_token **tokens)
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
