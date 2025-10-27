/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 07:23:44 by jde-carv          #+#    #+#             */
/*   Updated: 2025/10/27 07:50:11 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void red_out(char **args)
{
    int i;
    int fd;

	i = 0;
    while (args[i])
    {
        if (ft_strcmp(args[i], ">") == 0 && args[i + 1])
        {
            if (i == 0)
            {
                fprintf(stderr, "minishell: syntax error near unexpected token `>'\n");
                return;
            }
            fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			check_valid_fd(fd);
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
            args[i + 1] = NULL;
            i += 2;
            continue;
        }
        i++;
    }
}
void red_append(char **args)
{
    int i;
    int fd;

    i = 0;
    while (args[i])
    {
        if (ft_strcmp(args[i], ">>") == 0 && args[i + 1])
        {
            if (i == 0)
            {
                fprintf(stderr, "minishell: syntax error near unexpected token `>>'\n");
                return;
            }
            fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        }
    }
}

