/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_jessizabal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelzabal <mikelzabal@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:36:18 by mikelzabal        #+#    #+#             */
/*   Updated: 2025/05/30 12:48:03 by mzabal-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **dup_env(char **envp)
{
	int		i, count = 0;
	char	**new_env;

	while (envp[count])
		count++;
	new_env = malloc((count + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
}
void	ft_cleanup_shell(t_shell *shell)
{
	int	i;

	// Liberar el entorno duplicado
	if (shell->envp)
	{
		i = 0;
		while (shell->envp[i])
			free(shell->envp[i++]);
		free(shell->envp);
		shell->envp = NULL;
	}
	if (shell->cmds)
	{
		free_cmds(shell->cmds);
		shell->cmds = NULL;
	}
	if (shell->tokens)
	{
		free_tokens(shell->tokens);
		shell->tokens = NULL;
	}
}


int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line;

	(void)argc;
	(void)argv;
	shell.envp = dup_env(envp);
	shell.exit_status = 0;
	shell.tokens = NULL;
	shell.cmds = NULL;
	
	while (1)
	{
		setup_signals();
		line = readline("minishell> ");
		if (!line)
			break;
		if (*line)
			add_history(line);
		shell.tokens = tokenize_input(line);
		if (!shell.tokens || !validate_tokens(shell.tokens))
		{
			free_tokens(shell.tokens);
			shell.tokens = NULL;
			free(line);
			continue;
		}
		shell.cmds = parse_tokens(shell.tokens, &shell);
		if (!shell.cmds || preprocess_heredocs(shell.cmds))
		{
			free_tokens(shell.tokens);
			free_cmds(shell.cmds);
			shell.tokens = NULL;
			shell.cmds = NULL;
			free(line);
			continue;
		}
		t_cmd *tmp = shell.cmds;
		while (tmp)
		{
    		if (!tmp->is_builtin && tmp->argv && tmp->argv[0] && !tmp->full_path)
        		tmp->full_path = find_executable(tmp->argv[0], shell.envp);
    		tmp = tmp->next;
		}
		if (shell.cmds->next == NULL)
			execute_command(shell.cmds, &shell); // solo un comando
		else
			execute_pipeline(shell.cmds, &shell); // pipes

		// ✅ Limpieza al final de cada iteración
		free_tokens(shell.tokens);
		free_cmds(shell.cmds);
		shell.tokens = NULL;
		shell.cmds = NULL;
		free(line);
	}
	ft_cleanup_shell(&shell);
	return (shell.exit_status);
}

