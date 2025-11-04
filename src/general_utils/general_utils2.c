/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 07:14:56 by jde-carv          #+#    #+#             */
/*   Updated: 2025/11/04 17:04:26 by jde-carv         ###   ########.fr       */
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
void check_file_is_dir(const char *path)
{
    struct stat status;

    if (stat(path, &status) == 0 && S_ISDIR(status.st_mode))
    {
        write(2, "minishell: ", 11);
        write(2, path, ft_strlen(path));
        write(2, ": is a directory\n", 17);
        errno = EISDIR;
        return;
    }
}
