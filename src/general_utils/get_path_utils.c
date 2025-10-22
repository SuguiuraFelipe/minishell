/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:29:10 by devjorginho       #+#    #+#             */
/*   Updated: 2025/10/22 15:33:08 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *find_path_in_envp(char **envp, char *var_name)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(var_name);

	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, len) == 0 && envp[i][len] == '=')
			return envp[i] + len + 1;
		i++;
	}
	return NULL;
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
	char	*result;

	path_str = find_path_in_envp(envp, "PATH");
	if (!path_str)
		return (NULL);
	result = find_cmd_in_path(command, path_str);
	return (result);
}