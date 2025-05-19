/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:09:21 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/19 10:28:01 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(t_shell *shell, t_cmd *cmd)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->argc == 1)
	{
		printf("exit\n");
		exit_code = 1;
	}
	else if (cmd->argc > 2)
	{
		printf("exit: too many arguments\n");
		shell->exit_status = 1;
		return (1);
	}
	else if (cmd->argc == 2)
	{
		if (ft_is_numeric(cmd->argv[1]))
			exit_code = ft_atoi(cmd->argv[1]);
		else
		{
			printf("exit: %s: numeric argument required\n", cmd->argv[1]);
			exit_code = 255;
		}
	}
	ft_cleanup_shell(shell);
	exit(exit_code);
}
