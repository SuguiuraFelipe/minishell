/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:58:51 by devjorginho       #+#    #+#             */
/*   Updated: 2025/11/11 13:06:15 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*first_nonempty_arg(char **args)
{
	int	i;

	if (!args)
		return (NULL);
	i = 1;
	while (args[i])
	{
		if (args[i][0] != '\0')
			return (args[i]);
		i++;
	}
	return (NULL);
}

static char	*get_cd_arguments(char **args)
{
	char	*path;
	char	*arg;

	arg = first_nonempty_arg(args);
	if (arg)
		path = arg;
	else
		path = getenv("HOME");
	return (path);
}

static void	update_envp_variables(char **dup_envp, const char *var_name,
		const char *new_value)
{
	int		i;
	int		len;
	char	*new_str;

	i = 0;
	len = ft_strlen(var_name);
	new_str = malloc(len + 1 + ft_strlen(new_value) + 1);
	if (!new_str)
		return ;
	ft_strcpy(new_str, var_name);
	ft_strcat(new_str, "=");
	ft_strcat(new_str, new_value);
	while (dup_envp[i])
	{
		if (ft_strncmp(dup_envp[i], var_name, len) == 0
			&& dup_envp[i][len] == '=')
		{
			free(dup_envp[i]);
			dup_envp[i] = new_str;
			return ;
		}
		i++;
	}
	free(new_str);
}

static int	check_path_and_args(char **args, char *path, char *last_pwd)
{
	int	i;
	int	real_args;

	if (!path)
	{
		free(last_pwd);
		return (0);
	}
	i = 1;
	real_args = 0;
	while (args && args[i])
	{
		if (args[i][0] != '\0')
			real_args++;
		i++;
	}
	if (real_args > 1)
	{
		write(2, "cd: too many arguments\n", 23);
		free(last_pwd);
		return (0);
	}
	return (1);
}

void	exec_cd(char **args, char **dup_envp)
{
	char	current_path[MAX_DIR_SIZE];
	char	*last_pwd;
	char	*path;

	last_pwd = ft_strdup(find_path_in_envp(dup_envp, "PWD"));
	path = get_cd_arguments(args);
	if (!check_path_and_args(args, path, last_pwd))
		return ;
	if (path && ft_strcmp(path, ".") == 0)
	{
		free(last_pwd);
		return ;
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		free(last_pwd);
		return ;
	}
	if (getcwd(current_path, sizeof(current_path)))
	{
		update_envp_variables(dup_envp, "OLDPWD", last_pwd);
		update_envp_variables(dup_envp, "PWD", current_path);
	}
	free(last_pwd);
}
