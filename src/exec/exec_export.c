/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:03:11 by devjorginho       #+#    #+#             */
/*   Updated: 2025/10/25 19:04:46 by jde-carv         ###   ########.fr       */
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
static char	*var_concatenation(char *s1, char *s2, char *s3)
{
	char	*temp;
	char	*result;

	if (!s1 || !s2 || !s3)
		return (NULL);
	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, s3);
	free(temp);
	return (result);
}

void exec_export(char **args, char **dup_envp)
{
    int i;
    int j;
    char *new_var;
    char *var_value;

    j = 0;
    i = 1;
    while (args[i])
    {
        new_var = args[i];
        var_value = ft_strchr(new_var, '=');
        if (!var_value)
        {
            i++;
            continue;
        }
        *var_value = '\0';
        var_value++;
        if (!var_already_exist(dup_envp, var_value, new_var))
        {
            while (dup_envp[j])
                j++;
            dup_envp[j] = ft_strdup(var_concatenation(new_var, "=", var_value));
            dup_envp[j + 1] = NULL;
        }
        i++;
    }
}
