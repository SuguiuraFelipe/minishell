/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:02:09 by devjorginho       #+#    #+#             */
/*   Updated: 2025/11/12 18:04:08 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


static int	is_numeric_argument(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exec_exit(char **args, char **envp)
{
	long	exit_code;

	if (isatty(STDIN_FILENO))
		write(1, "exit\n", 5);
	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_status = 1;
		return ;
	}
	if (args[1])
	{
		if (!is_numeric_argument(args[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			free_split(envp);
			g_status = 2;
			exit(2);
		}
		exit_code = ft_atoi(args[1]);
		g_status = (unsigned char)exit_code;
	}
	free_split(envp);
	exit(g_status);
}
