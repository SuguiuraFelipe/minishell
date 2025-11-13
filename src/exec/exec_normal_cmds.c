/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_normal_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 08:41:47 by devjorginho       #+#    #+#             */
/*   Updated: 2025/11/13 20:27:52 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	path_is_dir_error(char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": is a directory\n", 2);
		exit(126);
	}
}

static void	init_and_check_execve(int pid, char *path, char **args, char **envp)
{
	int	status;

	if (pid == 0)
	{
		path_is_dir_error(path);
		execve(path, args, envp);
		handle_exec_error(args[0]);
		exit(1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_status = 128 + WTERMSIG(status);
	}
	else
	{
		perror("fork");
		g_status = 1;
	}
}

void	exec_normal_commands(char **args, char **envp, int original_stdin_fd)
{
	int	pid;
	char	*path;
	int	red_res;
	int	original_stdout_fd;

	if (!args || !args[0])
		return ;
	original_stdout_fd = dup(STDOUT_FILENO);
	red_res = redirections(args);
	if (red_res == -1 || !args[0])
	{
		dup2(original_stdin_fd, STDIN_FILENO);
		dup2(original_stdout_fd, STDOUT_FILENO);
		close(original_stdout_fd);
		return ;
	}
	path = get_path(args[0], envp);
	if (!path)
	{
		ft_cmd_not_found(args[0]);
		dup2(original_stdin_fd, STDIN_FILENO);
		dup2(original_stdout_fd, STDOUT_FILENO);
		close(original_stdout_fd);
		return ;
	}
	pid = fork();
	init_and_check_execve(pid, path, args, envp);
	dup2(original_stdin_fd, STDIN_FILENO);
	dup2(original_stdout_fd, STDOUT_FILENO);
	close(original_stdout_fd);
	free(path);
}
