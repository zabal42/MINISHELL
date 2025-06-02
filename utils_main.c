/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:58:23 by jessica           #+#    #+#             */
/*   Updated: 2025/06/02 09:13:01 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**dup_env(char **envp)
{
	int		i;
	int		count;
	char	**new_env;

	count = 0;
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

void	setup_shell(t_shell *shell, char **envp)
{
	shell->envp = dup_env(envp);
	shell->exit_status = 0;
	shell->tokens = NULL;
	shell->cmds = NULL;
}

void	cleanup_loop(t_shell *shell, char *line)
{
	free_tokens(shell->tokens);
	free_cmds(shell->cmds);
	shell->tokens = NULL;
	shell->cmds = NULL;
	free(line);
}

void	assign_cmds_full_path(t_cmd *cmds, char **envp)
{
	t_cmd	*tmp;

	tmp = cmds;
	while (tmp)
	{
		if (!tmp->is_builtin && tmp->argv && tmp->argv[0] && !tmp->full_path)
			tmp->full_path = find_executable(tmp->argv[0], envp);
		tmp = tmp->next;
	}
}
