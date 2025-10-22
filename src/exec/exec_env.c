/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:02:29 by devjorginho       #+#    #+#             */
/*   Updated: 2025/10/22 15:02:37 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void exec_env(char **args, char **dup_envp)
{
    int i;

    i = 0;
    (void) args;
    while(dup_envp[i])
    {
        printf("%s\n", dup_envp[i]);
        i++;
    }
}