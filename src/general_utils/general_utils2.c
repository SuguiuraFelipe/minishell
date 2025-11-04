/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 07:14:56 by jde-carv          #+#    #+#             */
/*   Updated: 2025/11/04 17:30:50 by fsuguiur         ###   ########.fr       */
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

void	handle_exec_error(char *cmd)
{
	if (errno == EACCES)
		ft_putstr_fd("minishell: Permission denied\n", 2);
	else if (errno == EISDIR)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
	}
	else if (errno == ENOENT)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
		perror("minishell");
	exit(126);
}
