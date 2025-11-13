/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 07:23:44 by jde-carv          #+#    #+#             */
/*   Updated: 2025/11/13 20:39:08 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	red_in(char **args, int i)
{
	int	fd;

	if (check_fail_red_simbol(args, i, "<"))
		return (-1);
	check_file_is_dir(args[i + 1]);
	if (errno == EISDIR)
		return (-1);
	fd = open(args[i + 1], O_RDONLY);
	if (fd == -1)
		return (-1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	ft_remove_redirection_tokens(args, i);
	return (0);
}

int	red_out(char **args, int i)
{
	int	fd;

	if (check_fail_red_simbol(args, i, ">"))
		return (-1);
	check_file_is_dir(args[i + 1]);
	if (errno == EISDIR)
		return (-1);
	fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	ft_remove_redirection_tokens(args, i);
	return (0);
}

int	red_append(char **args, int i)
{
	int	fd;

	if (check_fail_red_simbol(args, i, ">>"))
		return (-1);
	check_file_is_dir(args[i + 1]);
	if (errno == EISDIR)
		return (-1);
	fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (-1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	ft_remove_redirection_tokens(args, i);
	return (0);
}

void	red_here_doc(char **args, int i)
{
	int	pipefd[2];

	while (args[i])
	{
		if (ft_strcmp(args[i], "<<") == 0)
		{
			if (free_here_doc(args, i, "<<"))
				return ;
			if (pipe(pipefd) < 0)
				ft_perror("pipe");
			set_here_doc_line(pipefd, args, i);
			dup_and_close_here_doc(pipefd);
			free(args[i]);
			free(args[i + 1]);
			while (args[i + 2])
			{
				args[i] = args[i + 2];
				i++;
			}
			args[i] = NULL;
			break ;
		}
	}
}

int	redirections(char **args)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (args[i])
	{
		if (validate_quote_token(args, &i))
			continue ;
		if (!ft_strcmp(args[i], ">") || !ft_strcmp(args[i], ">>")
			|| !ft_strcmp(args[i], "<") || !ft_strcmp(args[i], "<<"))
		{
			check_redirection(args, &i, &error);
			if (error)
				return (-1);
			continue ;
		}
		else
			i++;
	}
	if (error)
		return (-1);
	if (!args[0])
		return (1);
	return (0);
}
