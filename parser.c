/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessica <jessica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:54:52 by mikelzabal        #+#    #+#             */
/*   Updated: 2025/05/30 19:25:57 by jessica          ###   ########.fr       */
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
** add_word_to_cmd:
** Añade una palabra (argumento) al array argv del comando actual.
** Incrementa argc y asegura que argv termina en NULL.
*/
void	add_word_to_cmd(t_cmd *cmd, char *word, t_shell *shell, t_quote_type quote)
{
	char	**new_argv;
	char	*expanded;
	int		i;

	if (quote == Q_SINGLE)
		expanded = ft_strdup(word);
	else
		expanded = expand_variables(word, shell->envp, shell->exit_status);

	// Reservamos espacio para los argumentos anteriores + nuevo + NULL final
	new_argv = malloc(sizeof(char *) * (cmd->argc + 2));
	if (!new_argv)
	{
		free(expanded);
		return ;
	}

	// Duplicamos cada string viejo de argv en el nuevo array
	i = 0;
	while (i < cmd->argc)
	{
		new_argv[i] = ft_strdup(cmd->argv[i]);
		i++;
	}
	// Insertamos el nuevo argumento expandido
	new_argv[i++] = expanded;
	new_argv[i] = NULL;

	// Liberamos el antiguo argv (y cada string dentro)
	if (cmd->argv)
	{
		int j = 0;
		while (cmd->argv[j])
			free(cmd->argv[j++]);
		free(cmd->argv);
	}

	// Actualizamos la estructura
	cmd->argv = new_argv;
	cmd->argc++;

	if (cmd->argc == 1)
		cmd->is_builtin = is_builtin_command(cmd->argv[0]);
}


/*
** handle_redirection:
** Procesa una redirección y la añade a la lista de redirecciones del comando.
** Avanza el puntero de token para saltar el archivo objetivo.
*/
void	handle_redirection(t_cmd *cmd, t_token **tokens, t_shell *shell)
{
	t_token	*redir = *tokens;
	t_token	*target = redir->next;
	t_redir	*new;

	if (!target || target->type != T_WORD)
	{
		cmd->error_message = ft_strdup("syntax error near unexpected token");
		return ;
	}
	new = malloc(sizeof(t_redir));
	if (!new)
		return ;
	new->target = expand_variables(target->value, shell->envp, shell->exit_status);
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
	add_redir_to_list(&cmd->redirections, new);
	*tokens = target -> next; // avanzamos
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
