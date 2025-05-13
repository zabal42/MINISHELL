/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:19:52 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/08 10:48:55 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**args;
	char	*command;

	(void)argc;
	(void)argv;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break;
		}
		if (*line)
			add_history(line);
		// Incluir el parseo de la línea en argumentos
		args = ft_split(line, ' ');
		if (!args || !args[0])
		{
			free(line);
			free_array(args);
			continue;
		}
		command = args[0];
		if (ft_strncmp(command, "exit", 4) == 0)
		{
			free(line);
			free_array(args);
			break;
		}
		execute_command(command, args, envp);
		free(line);
		free_array(args);
		//rl_clear_history();
	}
	rl_clear_history();
	return (0);
}
