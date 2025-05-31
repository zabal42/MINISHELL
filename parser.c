/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelzabal <mikelzabal@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:54:52 by mikelzabal        #+#    #+#             */
/*   Updated: 2025/05/31 12:14:06 by mikelzabal       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parser.h"

/*
** init_cmd:
** Crea e inicializa una estructura t_cmd vacía con valores por defecto.
** Devolverá un nuevo comando con campos preparados para rellenar.
*/
t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->argc = 0;
	cmd->full_path = NULL;
	cmd->is_builtin = 0;
	cmd->background = 0;
	cmd->input_fd = -1;
	cmd->output_fd = -1;
	cmd->error_message = NULL;
	cmd->redirections = NULL;
	cmd->next = NULL;
	return (cmd);
}

/*
** add_cmd_to_list:
** Añade un nuevo comando (t_cmd) a una lista enlazada de comandos.
** Útil cuando encontramos un pipe y se inicia una nueva estructura.
*/
void	add_cmd_to_list(t_cmd **head, t_cmd *new)
{
	t_cmd	*tmp;

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

/*
** clone_and_extend_argv:
** Clona el array argv existente y añade el argumento expanded al final.
** Devuelve el nuevo array o NULL en caso de error.
*/
static char	**clone_and_extend_argv(char **argv, int argc, char *expanded)
{
	char	**new_argv;
	int		i;

	new_argv = malloc(sizeof(char *) * (argc + 2));
	if (!new_argv)
		return (NULL);
	i = 0;
	while (i < argc)
	{
		new_argv[i] = ft_strdup(argv[i]);
		i++;
	}
	new_argv[i++] = expanded;
	new_argv[i] = NULL;
	return (new_argv);
}

/*
** add_word_to_cmd:
** Añade una palabra (argumento) al array argv del comando actual.
** Incrementa argc y asegura que argv termina en NULL.
*/
void	add_word_to_cmd(t_cmd *cmd, char *word,
			t_shell *shell, t_quote_type quote)
{
	char	**new_argv;
	char	*expanded;
	int		j;

	if (quote == Q_SINGLE)
		expanded = ft_strdup(word);
	else
		expanded = expand_variables(word, shell->envp, shell->exit_status);
	new_argv = clone_and_extend_argv(cmd->argv, cmd->argc, expanded);
	if (!new_argv)
	{
		free(expanded);
		return ;
	}
	if (cmd->argv)
	{
		j = 0;
		while (cmd->argv[j])
			free(cmd->argv[j++]);
		free(cmd->argv);
	}
	cmd->argv = new_argv;
	cmd->argc++;
	if (cmd->argc == 1)
		cmd->is_builtin = is_builtin_command(cmd->argv[0]);
}

/*
** init_redir_structure:
** Inicializa y devuelve una estructura t_redir a partir de los
** tokens y el shell.
** Devuelve NULL si hay error de sintaxis o fallo de malloc.
*/
static t_redir	*init_redir_structure(t_token *redir, t_shell *shell)
{
	t_token	*target;
	t_redir	*new;

	target = redir->next;
	if (!target || target->type != T_WORD)
		return (NULL);
	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->target = expand_variables(target->value, shell->envp,
			shell->exit_status);
	new->next = NULL;
	new->fd = -1;
	if (redir->type == T_REDIR_IN)
		new->type = REDIR_IN;
	else if (redir->type == T_REDIR_OUT)
		new->type = REDIR_OUT;
	else if (redir->type == T_REDIR_APPEND)
		new->type = REDIR_APPEND;
	else if (redir->type == T_HEREDOC)
		new->type = REDIR_HEREDOC;
	return (new);
}

/*
** handle_redirection:
** Procesa una redirección y la añade a la lista de redirecciones del comando.
** Avanza el puntero de token para saltar el archivo objetivo.
*/
void	handle_redirection(t_cmd *cmd, t_token **tokens, t_shell *shell)
{
	t_redir	*new;

	new = init_redir_structure(*tokens, shell);
	if (!new)
	{
		cmd->error_message = ft_strdup("syntax error near unexpected token");
		return ;
	}
	add_redir_to_list(&cmd->redirections, new);
	*tokens = (*tokens)->next->next;
}

/*
** add_redir_to_list:
** Añade una redirección a la lista enlazada dentro de un t_cmd.
*/

void	add_redir_to_list(t_redir **head, t_redir *new)
{
	t_redir	*tmp;

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
