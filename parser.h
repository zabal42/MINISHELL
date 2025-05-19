/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelzabal <mikelzabal@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:04:53 by mzabal-m          #+#    #+#             */
/*   Updated: 2025/05/19 12:31:42 by mikelzabal       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stddef.h> // para size_t

/* Tipos de tokens */
typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC
}	t_token_type;

/* Estructura básica de token */
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

/* Tipos de redirección */
typedef enum e_redir_type
{
	REDIR_IN,     // <
	REDIR_OUT,    // >
	REDIR_APPEND, // >>
	REDIR_HEREDOC // <<
}	t_redir_type;

/* Redirección asociada a un comando */
typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	struct s_redir	*next;
}	t_redir;

/* Comando completo parseado */
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

/* Tokenizer */
t_token	*tokenize_input(const char *line);
void	free_tokens(t_token *head);
void	print_tokens(t_token *head);
char	*concat_quoted_segments(const char *line, size_t *i);

/* Parser */
t_cmd	*parse_tokens(t_token *tokens);
t_cmd	*init_cmd(void);
void	add_word_to_cmd(t_cmd *cmd, char *word);
void	add_cmd_to_list(t_cmd **head, t_cmd *new);
void	handle_redirection(t_cmd *cmd, t_token **tokens);
void	add_redir_to_list(t_redir **head, t_redir *new);

/* Utils */
int		is_space(char c);
int		is_redirect_char(char c);
int		is_metachar(char c);
int		is_quote(char c);
int		check_closing_quote(const char *s);
void	print_cmds(t_cmd *cmd);
void	free_cmds(t_cmd *cmd);
void	free_redirections(t_redir *redir);

#endif
