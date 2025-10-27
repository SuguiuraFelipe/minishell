/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:33:46 by devjorginho       #+#    #+#             */
/*   Updated: 2025/10/27 07:43:02 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_builtin(char *s)
{
	if (!s)
		return (0);
	return (!ft_strcmp(s, "echo")
		|| !ft_strcmp(s, "cd")
		|| !ft_strcmp(s, "pwd")
		|| !ft_strcmp(s, "export")
		|| !ft_strcmp(s, "unset")
		|| !ft_strcmp(s, "env")
		|| !ft_strcmp(s, "exit"));
}
static int count_envp_vars(char **envp)
{
    int i = 0;
    while (envp[i])
        i++;
    return i;
}

static void free_envp(char **envp, int count)
{
    int i = 0;
    if (!envp)
        return;
    while (i < count)
    {
        free(envp[i]);
        i++;
    }
    free(envp);
}

static char **alloc_envp_copy(char **envp)
{
    char **result;
    int i;
    int len;
    int j;

    i = 0;
    result = malloc(sizeof(char *) * (count_envp_vars(envp) + 1));
    if (!result)
        return NULL;
    while (envp[i])
    {
        j = 0;
        while (envp[i][j])
            j++;
        len = j;
        result[i] = malloc(sizeof(char) * (len + 1));
        if (!result[i])
        {
            free_envp(result, i);
            return NULL;
        }
        i++;
    }
    result[i] = NULL;
    return result;
}

char **dup_envp(char **envp)
{
    char **copy;
    int i; 
	int j;

    copy = alloc_envp_copy(envp);
    if (!copy)
        return NULL;
    i = 0;
    while (envp[i])
    {
        j = 0;
        while (envp[i][j])
        {
            copy[i][j] = envp[i][j];
            j++;
        }
        copy[i][j] = '\0';
        i++;
    }
    return copy;
}
