/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelzabal <mikelzabal@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:00:42 by mzabal-m          #+#    #+#             */
/*   Updated: 2025/05/19 10:46:38 by mikelzabal       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "parser.h"

int	main(void)
{
	char	*line;
	t_token	*tokens;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break;
		if (*line)
		{
			tokens = tokenize_input(line);
			if (tokens)
			{
				print_tokens(tokens); // ← función de debug.c
				free_tokens(tokens);
			}
		}
		free(line);
	}
	return (0);
}
