/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelzabal <mikelzabal@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:18:04 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/27 11:51:38 by mikelzabal       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
int		validate_tokens(t_token *tok);
#endif

/*
gcc -Wall -Werror -Wextra builtins/builtin_pwd.c builtins/builtin_echo.c 
builtins/builtin_cd.c executor/execute_command.c main_jess.c builtins/path.c 
builtins/builtin_utils.c builtins/builtin_export.c builtins/builtin_unset.c 
builtins/builtin_env.c builtins/builtin_exit.c -Llibft -lft -lreadline
*/