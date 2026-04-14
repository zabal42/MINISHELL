/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessica <jessica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:18:04 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/31 13:43:44 by jessica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//# define _POSIX_C_SOURCE 199309L
# ifndef __APPLE__
#  define _XOPEN_SOURCE 700
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# ifdef __APPLE__
#  include <curses.h>
# else
#  include <ncurses.h>
# endif
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/inc/libft.h"
# include "parser.h"

//------------executor-------------------------------------
int		execute_command(t_cmd *cmd, t_shell *shell);
char	*find_executable(char *command, char **envp);
int		exec_builtin(t_cmd *cmd, t_shell *shell);
int		execute_pipeline(t_cmd *cmds, t_shell *shell);
int		open_redirections(t_cmd *cmd);
int		handle_heredoc(const char *delim);
int		preprocess_heredocs(t_cmd *cmds);
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
int		validate_tokens(t_token *tok);
char	**dup_env(char **envp);
void	setup_shell(t_shell *shell, char **envp);
void	cleanup_loop(t_shell *shell, char *line);
void	assign_cmds_full_path(t_cmd *cmds, char **envp);
//---------------------signals-----------------------------------------
void	handle_sigint(int sig);
void	setup_signals(void);
void	ignore_signals(void);
void	restore_signals(void);
#endif
