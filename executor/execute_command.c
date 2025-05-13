/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:20:11 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/13 13:01:52 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//int g_exit_status = 0;//Variable global para almacenar  "motivo de la salida"

int execute_command(char *command, char **args, char **envp)
{
	pid_t	pid;
	int		status;
	int		exit_status;

	exit_status = 0;
	if (ft_strncmp(command, "pwd", 3) == 0)
		return (ft_pwd());
	if (ft_strncmp(command, "echo", 4) == 0)
		return (ft_echo(args));
	if (ft_strncmp(command, "cd", 2) == 0)
		return (ft_cd(args, envp));
	if (!(access(command, X_OK) == 0))
	{
		command = find_executable(command, envp);
		if (!command)
		{
			printf("minishell: %s: command not found\n", args[0]);
			exit_status = 127;
			return (exit_status);
		}
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error al crear el proceso hijo");
		return (exit_status);
	}
	if (pid == 0)
	{
		if (execve(command, args, envp) == -1)
		{
			perror("Error al ejecutar el comando");
			exit(127);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (status == 0)
			exit_status = 0;
		else if (status == 127)
			exit_status = 127;
		else
			exit_status = 1;
	}
	return (exit_status);
}
