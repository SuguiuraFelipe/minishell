/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:29:42 by jde-carv          #+#    #+#             */
/*   Updated: 2025/10/31 20:12:53 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_status;

/* ========================================================= */
/* 1. detectar se é pipeline                                 */
/* ========================================================= */

int	ms_is_pipeline(char **cmdv)
{
	if (!cmdv || !cmdv[0])
		return (0);
	if (cmdv[1] == NULL)
		return (0);
	return (1);
}

/* ========================================================= */
/* 2. caminho sem pipe (reaproveita tudo o que já funciona)  */
/* ========================================================= */

void	ms_exec_single(char *cmdstr, char **envp, t_builtin_map *builtins)
{
	char	**args;

	if (!cmdstr || !*cmdstr)
		return ;
	/* split simples por enquanto */
	args = ft_split(cmdstr, ' ');
	if (!args)
		return ;
	exec_commands(args, envp, builtins);
	free_split(args);
}

/* ========================================================= */
/* 3. helpers para N comandos                                */
/* ========================================================= */

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

/* ========================================================= */
/* 4. fds do filho                                           */
/* ========================================================= */

static void	ms_setup_child_fds(int i, int ncmds, int **pipes)
{
	int	j;

	/* se não for o primeiro, lê do pipe anterior */
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	/* se não for o último, escreve no próximo pipe */
	if (i < ncmds - 1)
		dup2(pipes[i][1], STDOUT_FILENO);
	/* fecha tudo o que sobrou no filho */
	j = 0;
	while (j < ncmds - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

/*
** aqui é o lugar certo para aplicar redireções DENTRO do pipeline
** porque já estamos no filho e já trocámos stdin/stdout
*/
static void	ms_child_exec(char *cmdstr, char **envp, t_builtin_map *builtins)
{
	char	**args;

	args = ft_split(cmdstr, ' ');
	if (!args)
		exit(1);
	/* se o comando for "cmd > file" dentro do pipeline, trata aqui */
	redirections(args);
	exec_commands(args, envp, builtins);
	free_split(args);
	exit(g_status);
}

/* ========================================================= */
/* 5. executor de N comandos                                 */
/* ========================================================= */

void	ms_exec_pipeline(char **cmdv, char **envp, t_builtin_map *builtins)
{
	int		ncmds;
	int		**pipes;
	pid_t	*pids;
	int		i;
	int		status;

	ncmds = ms_count_cmds(cmdv);
	if (ncmds < 2)
	{
		ms_exec_single(cmdv[0], envp, builtins);
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
			ms_child_exec(cmdv[i], envp, builtins);
		}
		i++;
	}
	ms_close_all_pipes(pipes, ncmds);
	i = 0;
	while (i < ncmds)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
		i++;
	}
	ms_free_all_pipes(pipes, ncmds);
	free(pids);
}

/* ========================================================= */
/* 6. despachante global                                     */
/* ========================================================= */

void	ms_dispatch(char **cmdv, char **envp, t_builtin_map *builtins)
{
	if (!cmdv || !cmdv[0])
		return ;
	if (ms_is_pipeline(cmdv))
		ms_exec_pipeline(cmdv, envp, builtins);
	else
		ms_exec_single(cmdv[0], envp, builtins);
}
