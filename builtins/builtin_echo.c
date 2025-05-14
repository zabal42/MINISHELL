/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:06:02 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/14 09:50:57 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	flag;

	if(!cmd->argv || !cmd->argv[0])
		return (1);
	i = 1;
	flag = 0;
	while (cmd->argv[i] &&
		ft_strncmp("-n", cmd->argv[i], ft_strlen(cmd->argv[i])) == 0)
	{
		flag = 1;
		i++;
	}
	while (cmd->argv[i])
	{
		printf("%s", cmd->argv[i]);
		if (cmd->argv[i + 1])
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
	return (0);
}
