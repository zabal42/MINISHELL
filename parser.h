/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessica <jessica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:04:53 by mzabal-m          #+#    #+#             */
/*   Updated: 2025/05/29 19:20:28 by jessica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stddef.h> // para size_t

/* ───────────────────────────────
 * TIPOS DE DATOS Y ESTRUCTURAS
 * ─────────────────────────────── */

/* Tipos de tokens reconocidos por el lexer */
typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC
}	t_token_type;

/* Tipo de comillas de un token */
typedef enum e_quote_type
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}	t_quote_type;

/* Nodo de la lista de tokens */
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	t_quote_type	quote;
	struct s_token	*next;
}	t_token;

/* Tipos de redirección asociados a un comando */
typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

/* Nodo de la lista de redirecciones */
typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	int				fd;
	struct s_redir	*next;
}	t_redir;

/* Nodo de la lista de comandos */
typedef struct s_cmd
{
	char	**argv;
	int		argc;
	char	*full_path;
	int		is_builtin;
	int		background;
	int		input_fd;
	int		output_fd;
	char	*error_message;
	t_redir	*redirections;
	struct s_cmd *next;
}	t_cmd;

/* Estado general del shell (compartido con Jessi) */
typedef struct s_shell
{
	char	**envp;
	int		exit_status;
	t_token	*tokens;
	t_cmd	*cmds;
}	t_shell;

/* ───────────────────────────────
 * TOKENIZER
 * ─────────────────────────────── */

t_token	*tokenize_input(const char *line);
void	free_tokens(t_token *head);
void	print_tokens(t_token *head);
char	*concat_quoted_segments(const char *line, size_t *i);
int		is_builtin_command(const char *cmd);

/* ───────────────────────────────
 * PARSER
 * ─────────────────────────────── */

t_cmd	*parse_tokens(t_token *tokens, t_shell *shell);
t_cmd	*init_cmd(void);
void	add_word_to_cmd(t_cmd *cmd, char *word, t_shell *shell, t_quote_type quote);
void	add_cmd_to_list(t_cmd **head, t_cmd *new);
void	handle_redirection(t_cmd *cmd, t_token **tokens, t_shell *shell);
void	add_redir_to_list(t_redir **head, t_redir *new);

/* ───────────────────────────────
 * EXPANSIÓN DE VARIABLES
 * ─────────────────────────────── */

char	*expand_variables(const char *str, char **envp, int last_status);
char	*expand_env_variable(char *result, const char *str, size_t *i, char **envp);
char	*expand_status_code(char *result, int last_status);

/* ───────────────────────────────
 * FUNCIONES DE UTILIDAD
 * ─────────────────────────────── */

int		is_space(char c);
int		is_redirect_char(char c);
int		is_metachar(char c);
int		is_quote(char c);
int		check_closing_quote(const char *s);

void	print_cmds(t_cmd *cmd);
void	free_cmds(t_cmd *cmd);
void	free_redirections(t_redir *redir);

#endif