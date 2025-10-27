/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 07:14:56 by jde-carv          #+#    #+#             */
/*   Updated: 2025/10/27 17:31:01 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	check_valid_fd(int fd)
{
	if (fd < 0)
    {
        perror("open");
        return;
    }
}
void    ft_perror(char *s)
{
    perror(s);
    return;
}
