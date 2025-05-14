/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:59:50 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/14 09:49:22 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_pwd(t_shell *shell)
{
	char	*dir;

	dir = getcwd(NULL, 0); // Asigna memoria dinamicamente.
	if (!dir)
	{
		perror("pwd");
		shell->exit_status = 1;
		return (1);
	}
	printf("%s\n", dir);
	free(dir);
	shell->exit_status = 0;
	return (0);
}
