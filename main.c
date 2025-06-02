/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_jessizabal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessica <jessica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:36:18 by mikelzabal        #+#    #+#             */
/*   Updated: 2025/05/31 13:24:46 by jessica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	should_continue(t_shell *shell, char *line)
{
	free_tokens(shell->tokens);
	shell->tokens = NULL;
	free(line);
	return (1);
}

void	execute_shell_cmds(t_shell *shell)
{
	if (shell->cmds->next == NULL)
		execute_command(shell->cmds, shell);
	else
		execute_pipeline(shell->cmds, shell);
}

char	*get_input_line(void)
{
	char	*line;

	line = readline("minishell> ");
	if (!line)
		return (NULL);
	if (*line)
		add_history(line);
	return (line);
}

int	continue_with_cleanup(t_shell *shell, char *line)
{
	cleanup_loop(shell, line);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line;

	(void)argc;
	(void)argv;
	setup_shell(&shell, envp);
	while (1)
	{
		setup_signals();
		line = get_input_line();
		if (!line)
			break ;
		shell.tokens = tokenize_input(line);
		if (!shell.tokens || !validate_tokens(shell.tokens))
			if (should_continue(&shell, line))
				continue ;
		shell.cmds = parse_tokens(shell.tokens, &shell);
		if (!shell.cmds || preprocess_heredocs(shell.cmds))
			continue_with_cleanup(&shell, line);
		assign_cmds_full_path(shell.cmds, shell.envp);
		execute_shell_cmds(&shell);
		cleanup_loop(&shell, line);
	}
	ft_cleanup_shell(&shell);
	return (shell.exit_status);
}
