/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:02:09 by devjorginho       #+#    #+#             */
/*   Updated: 2025/11/11 17:08:16 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_exit(char **args, char **envp)
{
	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_status = 1;
		return;
	}
	free_split(envp);
	if (isatty(STDIN_FILENO))
		write(1, "exit\n", 5);
	exit(g_status);
}
