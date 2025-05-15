/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:18:04 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/15 12:06:51 by jesssanc         ###   ########.fr       */
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
}	t_cmd;*/

typedef struct	s_shell
{
	char	**envp;
	int		exit_status;
	//t_token	*tokens;
	t_cmd	*cmds;
}	t_shell;

//------------executor-------------------------------------
int 	execute_command(t_cmd *cmd, t_shell *shell);
char	*find_executable(char *command, char **envp);
//-----------builtins---------------------------------------
int		ft_pwd(t_shell *shell);
int		ft_echo(t_cmd *cmd);
int		ft_cd(t_shell *shell, t_cmd *cmd);
int	ft_export(t_shell *shell, t_cmd *cmd);
//------------------builtin utls------------------------------------
char	*get_key_value(char *key, t_shell *shell);
void	update_env_variable(t_shell *shell, char *key, char *new_value);
int		ft_is_valid_identifier(const char *str);
void	ft_add_or_update_env(t_shell *shell, const char *var_with_value);
char	**ft_realloc_env(char **envp, const char *new_entry);

//-------------------utils------------------------------
void	free_array(char **array);
#endif

/*
gcc -Wall -Werror -Wextra builtins/builtin_pwd.c builtins/builtin_echo.c 
builtins/builtin_cd.c executor/execute_command.c main_jess.c executor/path.c -Llibft -lft -lreadline
*/