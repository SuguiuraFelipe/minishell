/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:29:42 by jde-carv          #+#    #+#             */
/*   Updated: 2025/11/04 09:35:20 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_status;

int	ms_is_pipeline(char **cmdv)
{
	if (!cmdv || !cmdv[0])
		return (0);
	if (cmdv[1] == NULL)
		return (0);
	return (1);
}

void    ms_exec_single(char *cmdstr, char **envp, t_builtin_map *builtins, int original_stdin_fd)
{
    char    **args;

    if (!cmdstr || !*cmdstr)
        return ;
    args = ft_split(cmdstr, ' ');
    if (!args)
        return ;
    exec_commands(args, envp, builtins, original_stdin_fd);
    free_split(args);
}


static int	ms_count_cmds(char **cmdv)
{
	int	n;

	n = 0;
	while (cmdv[n])
		n++;
	return (n);
}

static int	**ms_create_pipes(int ncmds)
{
	int		i;
	int		**pipes;

	if (ncmds < 2)
		return (NULL);
	pipes = (int **)malloc(sizeof(int *) * (ncmds - 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < ncmds - 1)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (NULL);
		if (pipe(pipes[i]) == -1)
			return (NULL);
		i++;
	}
	return (pipes);
}

static void	ms_close_all_pipes(int **pipes, int ncmds)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < ncmds - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

static void	ms_free_all_pipes(int **pipes, int ncmds)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < ncmds - 1)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

static void	ms_setup_child_fds(int i, int ncmds, int **pipes)
{
	int	j;

	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < ncmds - 1)
		dup2(pipes[i][1], STDOUT_FILENO);
	j = 0;
	while (j < ncmds - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

static void ms_child_exec(char *cmdstr, char **envp, t_builtin_map *builtins, int original_stdin_fd)
{
    char    **args;

    args = ft_split(cmdstr, ' ');
    if (!args)
        exit(1);
    redirections(args);
    exec_commands(args, envp, builtins, original_stdin_fd);
    free_split(args);
    exit(g_status);
}


void    ms_exec_pipeline(char **cmdv, char **envp, t_builtin_map *builtins, int original_stdin_fd)
{
    int     ncmds;
    int     **pipes;
    pid_t   *pids;
    int     i;
    int     status;

    ncmds = ms_count_cmds(cmdv);
    if (ncmds < 2)
    {
        ms_exec_single(cmdv[0], envp, builtins, original_stdin_fd);
        return ;
    }
    pipes = ms_create_pipes(ncmds);
    if (!pipes)
        return ;
    pids = (pid_t *)malloc(sizeof(pid_t) * ncmds);
    if (!pids)
        return ;
    i = 0;
    while (i < ncmds)
    {
        pids[i] = fork();
        if (pids[i] == 0)
        {
            ms_setup_child_fds(i, ncmds, pipes);
            ms_child_exec(cmdv[i], envp, builtins, original_stdin_fd);
        }
        i++;
    }
    ms_close_all_pipes(pipes, ncmds);
    i = 0;
    while (i < ncmds)
    {
        waitpid(pids[i], &status, 0);
        
        if (i == ncmds - 1)
        {
            if (WIFEXITED(status))
                g_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                g_status = 128 + WTERMSIG(status);
        }
        i++;
    }
    ms_free_all_pipes(pipes, ncmds);
}

void    ms_dispatch(char **cmdv, char **envp, t_builtin_map *builtins, int original_stdin_fd)
{
    if (!cmdv || !cmdv[0])
        return ;
    if (ms_is_pipeline(cmdv))
        ms_exec_pipeline(cmdv, envp, builtins, original_stdin_fd); 
    else
        ms_exec_single(cmdv[0], envp, builtins, original_stdin_fd); 
}
