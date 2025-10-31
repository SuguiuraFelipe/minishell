/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_normal_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 13:29:11 by devjorginho       #+#    #+#             */
/*   Updated: 2025/10/31 20:13:21 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	init_and_check_execve(int pid, char *path,
						char **args, char **envp)
{
	if (pid == 0)
	{
		redirections(args);
		execve(path, args, envp);
		perror("execve");
		exit(1);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		perror("fork");
}

void	exec_normal_commands(char **args, char **envp)
{
	int		pid;
	char	*path;

	if (!args || !args[0])
		return ;
	path = get_path(args[0], envp);
	if (!path)
	{
		ft_cmd_not_found(args[0]);
		return ;
	}
	pid = fork();
	init_and_check_execve(pid, path, args, envp);
	free(path);
}
