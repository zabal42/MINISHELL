/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_jess.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:19:52 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/16 12:50:17 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **ft_copy_env(char **envp)
{
	int		i;
	char	**new_env;
	
	i = 0;
	while (envp[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			free_array(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_cmd	cmd;
	char	*line;

	(void)argc;
	(void)argv;

	// Inicializar la estructura t_shell
	shell.envp = ft_copy_env(envp);
	shell.exit_status = 0;

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

		// Inicializar todos los campos de t_cmd
		cmd.argv = ft_split(line, ' ');
		cmd.argc = 0;
		cmd.full_path = NULL;
		cmd.is_builtin = 0;
		cmd.background = 0;
		while (cmd.argv && cmd.argv[cmd.argc])
			cmd.argc++;
		if (!cmd.argv || !cmd.argv[0])
		{
			free(line);
			free_array(cmd.argv);
			continue;
		}
		/*if (ft_strncmp(cmd.argv[0], "exit", 4) == 0)
		{
			free(line);
			free_array(cmd.argv);
			break;
		}*/

		// Llamar a execute_command con las estructuras
		if (cmd.argc > 0)
			execute_command(&cmd, &shell);

		// Liberar memoria
		free(line);
		free_array(cmd.argv);
	}
	//free_array(shell.envp);
	rl_clear_history();
	return (shell.exit_status);
}
