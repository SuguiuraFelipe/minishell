/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 20:33:48 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/10/28 18:01:33 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int g_status = 0;

static void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
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
	(void) ac;
	(void) av;
	return;
}

int	main(int ac, char **av, char **envp)
{
	do_not_return(ac, av);
	char			*line;
	char			**result;
	char			**duplicated_env;
	t_builtin_map	builtins[8];

	duplicated_env = dup_envp(envp);
	init_builtin_map(builtins);
	setup_signal_handlers();
	while (1)
	{
		line = read_line_or_exit();
		if (!line)
			continue ;
		result = parse_pipeline(line);
		if (!result)
		{
			free(line);
			continue ;
		}
		exec_commands(result, duplicated_env, builtins);
		free_split(result);
		free(line);
	}
	return (0);
}

