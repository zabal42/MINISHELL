/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:04:53 by mzabal-m          #+#    #+#             */
/*   Updated: 2025/05/19 13:04:02 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,		// <
	T_REDIR_OUT,	// >
	T_REDIR_APPEND,	// >>
	T_HEREDOC		// <<
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char		**argv;
	int			argc;
	char		*full_path;
	int			is_builtin;
	int			background;
	int			input_fd;
	int			output_fd;
	char		*error_message;
	void		*redirections;
	struct s_cmd	*next;
}	t_cmd;
/*
typedef struct s_redir
{
	t_token_type	type;      // El tipo de redirección (<, >, >>, <<)
	char			*target;  // El fichero objetivo (o delimitador heredoc)
	struct s_redir	*next;      // Para listas enlazadas de redirecciones
}	t_redir; */

/* Tokenizer */
t_token	*tokenize_input(const char *line);
void	free_tokens(t_token *head);
void	print_tokens(t_token *head);

/* Utils parser */
int		is_space(char c);
int		is_redirect_char(char c);
int		is_metachar(char c);
int		is_quote(char c);

#endif
