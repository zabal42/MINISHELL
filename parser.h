/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabal-m <mzabal-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:04:53 by mzabal-m          #+#    #+#             */
/*   Updated: 2025/05/12 12:11:18 by mzabal-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**argv;
	char			*infile;
	char			*outfile;
	int				append;
	char			*heredoc_delim;
	struct s_cmd	*next;
}	t_cmd;

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
