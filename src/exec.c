/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 13:29:11 by devjorginho       #+#    #+#             */
/*   Updated: 2025/10/21 11:30:03 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_path(char *command, char **envp)
{
	int i;
	char *string_path;
	char **command_path;
	char *path_result;

	i = 0;
	string_path = NULL;
	while(envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			string_path = envp[i] + 5;
			break;
		}
		i++;
	}
	if(!string_path)
		return (NULL);
	command_path = ft_split(string_path, ':');
	i = 0;
	while (command_path && command_path[i])
	{
		path_result = cat_path_and_cmd(command_path[i], "/", command);
		if (access(path_result, X_OK) == 0)
		{
			free_split(command_path);
			return (path_result);
		}
		free(path_result);
		i++;
	}
	free_split(command_path);
	return (NULL);
}

void	exec_normal_commands(char **args, char **envp)
{
	int		pid;
	char	*path;

	if (!args || !args[0])
		return;
	path = get_path(args[0], envp);
	if (!path)
	{
		printf("minishell: %s: comando nao ta aqki\n", args[0]);
		return;
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
