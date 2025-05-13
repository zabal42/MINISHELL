/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:59:50 by jesssanc          #+#    #+#             */
/*   Updated: 2025/05/13 13:01:10 by jesssanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_pwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0); // Asigna memoria dinamicamente.
	if (!dir)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", dir);
	free(dir);
	return (0);
}
