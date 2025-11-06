/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:01:51 by devjorginho       #+#    #+#             */
/*   Updated: 2025/11/06 18:36:33 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_echo(char **args, char **envp)
{
	int		i;
	char	*clean;

	(void)envp;
	i = 1;
	while (args[i])
	{
		clean = remove_quotes(args[i]);
		ft_putstr_fd(clean, 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		free(clean);
		i++;
	}
	ft_putstr_fd("\n", 1);
}
