/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:18:04 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/13 12:59:40 by jesssanc         ###   ########.fr       */
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
}	t_shell;

int		execute_command(char *command, char **args, char **envp);
void	free_array(char **array);
char	*find_executable(char *command, char **envp);
int		ft_pwd(void);
int		ft_echo(char **args);
int		ft_cd(char **args, char **envp);

#endif

/*
gcc -Wall -Werror -Wextra builtins/builtin_pwd.c builtins/builtin_echo.c 
builtins/builtin_cd.c executor/execute_command.c main_jess.c executor/path.c -Llibft -lft -lreadline
*/