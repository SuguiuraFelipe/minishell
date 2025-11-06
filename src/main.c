/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:59:33 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/11/06 19:28:16 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int			g_status = 0;

static void	minishell_loop(char **envp, t_builtin_map *builtins,
		int original_stdin_fd)
{
	char	*line;
	char	**cmdv;
	char	*temp_result[2];

	while (1)
	{
		line = read_line_or_exit();
		if (!line)
			continue ;
		temp_result[0] = line;
		temp_result[1] = NULL;
		expand_amb_variables(envp, temp_result);
		line = temp_result[0];
		cmdv = parse_pipeline(line);
		free(line);
		if (!cmdv)
			continue ;
		dispatch(cmdv, envp, builtins, original_stdin_fd);
		free_split(cmdv);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_builtin_map	builtins[8];
	int				original_stdin_fd;

	(void)argc;
	(void)argv;
	original_stdin_fd = dup(STDIN_FILENO);
	if (original_stdin_fd == -1)
		perror("dup");
	init_builtin_map(builtins);
	minishell_loop(envp, builtins, original_stdin_fd);
	return (0);
}
