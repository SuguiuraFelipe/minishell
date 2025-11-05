/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:29:42 by jde-carv          #+#    #+#             */
/*   Updated: 2025/11/05 16:57:12 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void child_exec(char *str, char **envp, t_builtin_map *builtins, 
    int original_stdin_fd)
{
    char    **args;

    args = ft_split(str, ' ');
    if (!args)
        exit(1);
    redirections(args);
    exec_commands(args, envp, builtins, original_stdin_fd);
    free_split(args);
    exit(g_status);
}


static void	create_children(char **args, char **envp, t_builtin_map *builtins,
	int **pipes, int original_stdin_fd, pid_t *pids, int ncmds)
{
	int	i;

	i = -1;
	while (++i < ncmds)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			setup_child_fds(i, ncmds, pipes);
			child_exec(args[i], envp, builtins, original_stdin_fd);
		}
	}
}

static void	wait_and_cleanup(pid_t *pids, int ncmds, int **pipes)
{
	int	i;
	int	status;

	close_all_pipes(pipes, ncmds);
	i = -1;
	while (++i < ncmds)
	{
		waitpid(pids[i], &status, 0);
		if (i == ncmds - 1)
		{
			if (WIFEXITED(status))
				g_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_status = 128 + WTERMSIG(status);
		}
	}
	free_all_pipes(pipes, ncmds);
}

void	exec_pipeline(char **args, char **envp, t_builtin_map *builtins,
	int original_stdin_fd)
{
	int		ncmds;
	int		**pipes;
	pid_t	*pids;

	ncmds = count_cmds(args);
	if (ncmds < 2)
		return (exec_single(args[0], envp, builtins, original_stdin_fd));
	pipes = create_pipes(ncmds);
	if (!pipes)
		return ;
	pids = malloc(sizeof(pid_t) * ncmds);
	if (!pids)
		return ;
	create_children(args, envp, builtins, pipes, original_stdin_fd, pids, ncmds);
	wait_and_cleanup(pids, ncmds, pipes);
}

void    dispatch(char **args, char **envp, t_builtin_map *builtins, 
    int original_stdin_fd)
{
    if (!args || !args[0])
        return ;
    if (is_pipeline(args))
        exec_pipeline(args, envp, builtins, original_stdin_fd); 
    else
        exec_single(args[0], envp, builtins, original_stdin_fd); 
}
