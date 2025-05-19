/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelzabal <mikelzabal@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:00:42 by mzabal-m          #+#    #+#             */
/*   Updated: 2025/05/19 13:22:54 by mikelzabal       ###   ########.fr       */
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
	t_cmd	*cmds;

	while (1)
	{
		
		/*line = readline("minishell> ");
		if (!line)
			break;
		if (*line)
		{
			add_history(line);
			tokens = tokenize_input(line);
			if (tokens)
			{
				cmds = parse_tokens(tokens);
				if (cmds)
				{
					print_cmds(cmds);
					free_cmds(cmds);
				}
				free_tokens(tokens);
			}
		}*/
		line = readline("minishell> ");
		if (!line)
			break;
		if (*line)
		{
			add_history(line);
			printf("⏩ línea leída: %s\n", line);

			tokens = tokenize_input(line);
			if (!tokens)
				printf("❌ tokenize_input devolvió NULL\n");
			else
			{
				printf("✅ tokenize_input OK\n");
				print_tokens(tokens); // usa versión printf

				cmds = parse_tokens(tokens);
				if (!cmds)
					printf("❌ parse_tokens devolvió NULL\n");
				else
				{
					printf("✅ parse_tokens OK\n");
					print_cmds(cmds);
					free_cmds(cmds);
				}
				free_tokens(tokens);
			}
	}
		free(line);
		
	
	}
	return (0);
}


