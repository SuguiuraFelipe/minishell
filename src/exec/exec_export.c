/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:03:11 by devjorginho       #+#    #+#             */
/*   Updated: 2025/10/25 17:42:26 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int var_already_exist(char **dup_envp, char *var_name, char *new_var)
{
    int j;
    int len;

    len = ft_strlen(var_name);
    j = 0;
    while (dup_envp[j])
    {
        if (ft_strncmp(dup_envp[j], var_name, len) == 0 && dup_envp[j][len] == '=')
        {
            free(dup_envp[j]);
            dup_envp[j] = ft_strdup(new_var);
            return 1;
        }
        j++;
    }
    return 0;
}

void exec_export(char **args, char **dup_envp)
{
    int i;
    char *new_var;
    char *var_name;

    i = 1;
    while (args[i])
    {
        new_var = args[i];
        var_name = ft_strchr(new_var, '=');
        if (!var_name)
            continue;
        *var_name = '\0';
        var_name = new_var;

        if (!var_already_exist(dup_envp, var_name, new_var))
        {
            int j = 0;
            while (dup_envp[j])
                j++;
            dup_envp[j] = ft_strdup(new_var);
            dup_envp[j + 1] = NULL;
        }
        i++;
    }
}
