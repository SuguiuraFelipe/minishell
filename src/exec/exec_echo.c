/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:01:51 by devjorginho       #+#    #+#             */
/*   Updated: 2025/10/25 17:08:21 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void exec_echo(char **args, char **dup_envp)
{
    int i;
    int remove_new_line;
	
    i = 1;
    remove_new_line = 0;
    (void)dup_envp;
    while (args[i] && ft_strcmp(args[i], "-n") == 0)
    {
        remove_new_line = 1;
        i++;
    }
    while (args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }
    if (!remove_new_line)
        printf("\n");
}
