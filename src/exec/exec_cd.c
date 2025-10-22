/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:58:51 by devjorginho       #+#    #+#             */
/*   Updated: 2025/10/22 15:29:15 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char *get_cd_arguments(char **args)
{
	char *path;

	if(args[1])
		path = args[1];
	else
        path = getenv("HOME");
	return (path);
}
static void update_envp_variables(char **dup_envp, const char *var_name, const char *new_value)
{
	int i;
	int len;
    char *new_str;

    i = 0;
    len = ft_strlen(var_name);
    new_str = malloc(len + 1 + ft_strlen(new_value) + 1);
    if (!new_str)
        return;
    ft_strcpy(new_str, var_name);
    ft_strcat(new_str, "=");
	ft_strcat(new_str, new_value);
    while (dup_envp[i])
    {
        if (ft_strncmp(dup_envp[i], var_name, len) == 0 && dup_envp[i][len] == '=')
        {
            free(dup_envp[i]);
            dup_envp[i] = new_str;
            return;
        }
        i++;
    }
    free(new_str);
}

void exec_cd(char **args, char **dup_envp)
{
    char current_path[MAX_DIR_SIZE];
    char *last_pwd;
    char *path;

    last_pwd = ft_strdup(find_path_in_envp(dup_envp, "PWD"));
    path = get_cd_arguments(args);
    if (!path)
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