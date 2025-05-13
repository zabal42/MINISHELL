/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabal-m <mzabal-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:59:44 by mzabal-m          #+#    #+#             */
/*   Updated: 2025/05/12 12:16:16 by mzabal-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser.h"

const char *token_type_str(t_token_type type)
{
	if (type == T_WORD)
		return ("WORD");
	if (type == T_PIPE)
		return ("PIPE");
	if (type == T_REDIR_IN)
		return ("REDIR_IN");
	if (type == T_REDIR_OUT)
		return ("REDIR_OUT");
	if (type == T_REDIR_APPEND)
		return ("REDIR_APPEND");
	if (type == T_HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

void print_tokens(t_token *head)
{
	while (head)
	{
		printf("Token: %-12s | Value: '%s'\n", token_type_str(head->type), head->value);
		head = head->next;
	}
}
