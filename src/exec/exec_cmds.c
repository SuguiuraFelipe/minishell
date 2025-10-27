/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:06:13 by devjorginho       #+#    #+#             */
/*   Updated: 2025/10/25 19:18:20 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_builtin_map(t_builtin_map *builtins)
{
	builtins[0].name = "echo";
	builtins[0].func = exec_echo;
	builtins[1].name = "cd";
	builtins[1].func = exec_cd;
	builtins[2].name = "pwd";
	builtins[2].func = exec_pwd;
	builtins[3].name = "export";
	builtins[3].func = exec_export;
	builtins[4].name = "unset";
	builtins[4].func = exec_unset;
	builtins[5].name = "env";
	builtins[5].func = exec_env;
	builtins[6].name = "exit";
	builtins[6].func = exec_exit;
	builtins[7].name = NULL;
	builtins[7].func = NULL;
}

void	exec_commands(char **args, char **envp, t_builtin_map *builtins)
{
	int	i;

	i = 0;
	expand_amb_variables(envp, args);
	while (builtins[i].name)
	{
		if (!ft_strcmp(args[0], builtins[i].name))
		{
			builtins[i].func(args, envp);
			return ;
		}
		i++;
	}
	exec_normal_commands(args, envp);
}
