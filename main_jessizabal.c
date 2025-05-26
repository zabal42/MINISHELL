/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_jessizabal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessica <jessica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:36:18 by mikelzabal        #+#    #+#             */
/*   Updated: 2025/05/26 19:23:16 by jessica          ###   ########.fr       */
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
	}

	// Por si acaso quedan comandos o tokens colgados (seguridad extra)
	if (shell->cmds)
		free_cmds(shell->cmds);
	if (shell->tokens)
		free_tokens(shell->tokens);
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
	shell.cmds = init_cmd();

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break;
		if (*line)
			add_history(line);

		shell.tokens = tokenize_input(line);
		if (!shell.tokens)
		{
			free(line);
			continue;
		}

		shell.cmds = parse_tokens(shell.tokens, &shell);
		t_cmd *tmp = shell.cmds;
		while (tmp)
		{
    		if (!tmp->is_builtin && tmp->argv && tmp->argv[0] && !tmp->full_path)
        		tmp->full_path = find_executable(tmp->argv[0], shell.envp);
    		tmp = tmp->next;
		}
		if (shell.cmds)
			execute_pipeline(shell.cmds, &shell);

		free_tokens(shell.tokens);
		free_cmds(shell.cmds);
		free(line);
	}
	ft_cleanup_shell(&shell);
	return (shell.exit_status);
}
