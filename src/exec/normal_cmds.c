/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 13:29:11 by devjorginho       #+#    #+#             */
/*   Updated: 2025/10/22 15:15:56 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_normal_commands(char **args, char **envp)
{
	int		pid;
	char	*path;

	if (!args || !args[0])
		return;
	path = get_path(args[0], envp);
	if (!path)
	{
		ft_cmd_not_found(args[0]);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		execve(path, args, envp);
		perror("execve");
		exit(1);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		perror("fork");

	free(path);
}
