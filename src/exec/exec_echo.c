/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:27:18 by jde-carv          #+#    #+#             */
/*   Updated: 2025/11/13 21:54:17 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_valid_n_flag(char *s)
{
	int	i;

	if (!s || ft_strlen(s) < 2 || s[0] != '-' || s[1] != 'n')
		return (0);
	i = 2;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	handle_multi_n(char **args, int *i, int *print_newline)
{
	while (args[*i] && is_valid_n_flag(args[*i]))
	{
		*print_newline = 0;
		(*i)++;
	}
}

static char	*echo_collect_token(char **args, int *i)
{
	char	*clean;
	int		j;

	if (!is_broken_start(args[*i]) || !args[*i + 1])
		return (ft_strdup(args[*i]));
	clean = ft_strdup(args[*i]);
	if (!clean)
		return (NULL);
	j = *i + 1;
	while (args[j] && !is_broken_end(args[j]))
	{
		clean = safe_strjoin(clean, args[j]);
		if (!clean)
			return (NULL);
		j++;
	}
	if (args[j] && is_broken_end(args[j]))
	{
		clean = safe_strjoin(clean, args[j]);
		if (!clean)
			return (NULL);
		*i = j;
	}
	return (clean);
}

static void	echo_print(char *clean)
{
	ft_putstr_fd(clean, 1);
}

void	exec_echo(char **args, char **envp)
{
	int		i;
	int		print_newline;
	char	*clean;

	(void)envp;
	i = 1;
	print_newline = 1;
	handle_multi_n(args, &i, &print_newline);
	while (args[i])
	{
		clean = echo_collect_token(args, &i);
		if (!clean)
			return ;
		echo_print(clean);
		free(clean);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (print_newline)
		ft_putstr_fd("\n", 1);
}
