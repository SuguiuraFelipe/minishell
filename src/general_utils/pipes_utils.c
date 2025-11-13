/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:23:45 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/11/13 21:36:48 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_status;

int	is_pipeline(char **args)
{
	if (!args || !args[0])
		return (0);
	if (args[1] == NULL)
		return (0);
	return (1);
}

void	exec_single(char *str, char **envp, t_builtin_map *builtins,
		int original_stdin_fd)
{
	char	**args;

	if (!str || !*str)
		return ;
	args = split_args_with_quotes(str);
	if (!args)
		return ;
	exec_commands(args, envp, builtins, original_stdin_fd);
	free_split(args);
}

int	count_cmds(char **args)
{
	int	n;

	n = 0;
	while (args[n])
		n++;
	return (n);
}

int	**create_pipes(int ncmds)
{
	int	i;
	int	**pipes;

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

void	close_all_pipes(int **pipes, int ncmds)
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
