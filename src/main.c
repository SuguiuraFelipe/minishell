/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:59:33 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/11/12 17:44:17 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	g_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	handle_sigquit(int sig)
{
	(void)sig;
}

static void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}

int			g_status = 0;

static void	minishell_loop(char **envp, t_builtin_map *builtins,
		int original_stdin_fd)
{
	char	*line;
	char	**cmdv;

	while (1)
	{
		line = read_line_or_exit();
		if (!line)
			continue ;
		line = expand_line_before_split(line, envp);
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
	char			**duplicated;

	(void)argc;
	(void)argv;
	original_stdin_fd = dup(STDIN_FILENO);
	if (original_stdin_fd == -1)
		perror("dup");
	duplicated = dup_envp(envp);
	update_shlvl(duplicated);
	init_builtin_map(builtins);
	setup_signals();
	minishell_loop(duplicated, builtins, original_stdin_fd);
	return (0);
}
