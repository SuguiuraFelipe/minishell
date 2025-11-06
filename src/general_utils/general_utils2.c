/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 07:14:56 by jde-carv          #+#    #+#             */
/*   Updated: 2025/11/06 20:00:38 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	check_valid_fd(int fd)
{
	if (fd < 0)
	{
		perror("open");
		return ;
	}
}

void	ft_perror(char *s)
{
	perror(s);
	return ;
}

void	check_file_is_dir(const char *path)
{
	struct stat	status;

	if (stat(path, &status) == 0 && S_ISDIR(status.st_mode))
	{
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": is a directory\n", 17);
		errno = EISDIR;
		return ;
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

int	check_identifier(char *name)
{
	int	i;

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
	{
		write(2, "minishell: export: `", 21);
		write(2, name, ft_strlen(name));
		write(2, "': not a valid identifier\n", 27);
		return (0);
	}
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			write(2, "minishell: export: `", 21);
			write(2, name, ft_strlen(name));
			write(2, "': not a valid identifier\n", 27);
			return (0);
		}
		i++;
	}
	return (1);
}
