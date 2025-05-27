/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:18:04 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/27 11:06:33 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//# define _POSIX_C_SOURCE 199309L
# define _XOPEN_SOURCE 700

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <curses.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/inc/libft.h"
# include "parser.h"

/*
typedef	struct s_cmd
{
	char		**argv;
	char		*infile;
	char		*outfile;
	int			append;
	char		*heredoc_delim;
	struct s_cmd	*next;
}	t_cmd;

typedef struct	s_shell
{
	char	**envp;
	int		exit_status;
	//t_token	*tokens;
	t_cmd	*cmds;
}	t_shell; */

//------------executor-------------------------------------
int 	execute_command(t_cmd *cmd, t_shell *shell);
char	*find_executable(char *command, char **envp);
int		exec_builtin(t_cmd *cmd, t_shell *shell);
int		execute_pipeline(t_cmd *cmds, t_shell *shell);
int		open_redirections(t_cmd *cmd);
int		handle_heredoc(const char *delim);
//-----------builtins---------------------------------------
int		ft_pwd(t_shell *shell);
int		ft_echo(t_cmd *cmd);
int		ft_cd(t_shell *shell, t_cmd *cmd);
int		ft_export(t_shell *shell, t_cmd *cmd);
int		ft_unset(t_shell *shell, t_cmd *cmd);
int		ft_env(t_shell *shell, t_cmd *cmd);
int		ft_exit(t_shell *shell, t_cmd *cmd);
//------------------builtin utls------------------------------------
char	*get_key_value(char *key, t_shell *shell);
void	update_env_variable(t_shell *shell, char *key, char *new_value);
int		ft_is_valid_identifier(const char *str);
void	ft_add_or_update_env(t_shell *shell, const char *var_with_value);
char	**ft_realloc_env(char **envp, const char *new_entry);
void	ft_remove_from_env(t_shell *shell, const char *key);
int		ft_is_numeric(const char *str);
//-------------------utils------------------------------
void	free_array(char **array);
void	ft_cleanup_shell(t_shell *shell);
//---------------------signals-----------------------------------------
void	handle_sigint(int sig);
void	setup_signals(void);
#endif
