/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:02:09 by devjorginho       #+#    #+#             */
/*   Updated: 2025/10/22 15:29:32 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void exec_exit(char **args, char **dup_envp)
{
	(void)args;
    (void)dup_envp;
    exit(0);
}