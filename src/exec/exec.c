/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 13:29:11 by devjorginho       #+#    #+#             */
/*   Updated: 2025/10/21 12:12:13 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*find_path_in_envp(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*find_cmd_in_path(char *command, char *path_str)
{
	char	**path_dirs;
	char	*full_path;
	int		i;

	if (!path_str)
		return (NULL);
	path_dirs = ft_split(path_str, ':');
	if (!path_dirs)
		return (NULL);
	i = 0;
	while (path_dirs[i])
	{
		full_path = cat_path_and_cmd(path_dirs[i], "/", command);
		if (access(full_path, X_OK) == 0)
		{
			free_split(path_dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split(path_dirs);
	return (NULL);
}
char	*get_path(char *command, char **envp)
{
	char	*path_str;

	path_str = find_path_in_envp(envp);
	if (!path_str)
		return (NULL);
	return (find_cmd_in_path(command, path_str));
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
