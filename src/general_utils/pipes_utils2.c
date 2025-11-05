/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:24:58 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/11/05 16:57:22 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_status;

void	setup_child_fds(int i, int ncmds, int **pipes)
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

void	free_all_pipes(int **pipes, int ncmds)
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
