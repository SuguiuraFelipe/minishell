/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 20:33:48 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/11/06 16:23:46 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int			g_status = 0;

static void	handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_status = 130;
}

static void	setup_signal_handlers(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	do_not_return(int ac, char **av)
{
	(void)ac;
	(void)av;
}

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
		cmdv = parse_pipeline(line);
		free(line);
		if (!cmdv)
			continue ;
		dispatch(cmdv, envp, builtins, original_stdin_fd);
		free_split(cmdv);
	}
}

int	main(int ac, char **av, char **envp)
{
	char			**duplicated_env;
	t_builtin_map	builtins[8];
	int				original_stdin_fd;

	do_not_return(ac, av);
	original_stdin_fd = dup(STDIN_FILENO);
	if (original_stdin_fd == -1)
	{
		perror("dup");
		return (1);
	}
	duplicated_env = dup_envp(envp);
	init_builtin_map(builtins);
	setup_signal_handlers();
	minishell_loop(duplicated_env, builtins, original_stdin_fd);
	close(original_stdin_fd);
	return (0);
}
