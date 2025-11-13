/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:22:16 by jde-carv          #+#    #+#             */
/*   Updated: 2025/11/13 20:29:02 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_fail_red_simbol(char **args, int i, char *simbol)
{
	char	*simbols[5];
	int		j;

	j = 0;
	simbols[0] = ">";
	simbols[1] = ">>";
	simbols[2] = "<";
	simbols[3] = "<<";
	simbols[4] = NULL;
	if (!args[i + 1])
	{
		while (simbols[j])
		{
			if (!ft_strcmp(simbol, simbols[j]))
			{
				write(2, "minishell: syntax error near unexpected token `", 48);
				write(2, simbols[j], ft_strlen(simbols[j]));
				write(2, "'\n", 2);
				return (1);
			}
			j++;
		}
	}
	return (0);
}

int	free_here_doc(char **args, int i, char *simbol)
{
	if (check_fail_red_simbol(args, i, simbol))
	{
		free(args[i]);
		args[i] = NULL;
		return (1);
	}
	return (0);
}

char	*set_here_doc_line(int *arr, char **args, int i)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, args[i + 1]) == 0)
			break ;
		write(arr[1], line, strlen(line));
		write(arr[1], "\n", 1);
		free(line);
	}
	return (line);
}

void	dup_and_close_here_doc(int *arr)
{
	dup2(arr[0], STDIN_FILENO);
	close(arr[0]);
	close(arr[1]);
}

void	check_redirection(char **args, int *i, int *error)
{
	if (!ft_strcmp(args[*i], ">"))
	{
		if (red_out(args, *i) == -1)
			*error = 1;
	}
	else if (!ft_strcmp(args[*i], ">>"))
	{
		if (red_append(args, *i) == -1)
			*error = 1;
	}
	else if (!ft_strcmp(args[*i], "<"))
	{
		if (red_in(args, *i) == -1)
			*error = 1;
	}
	else if (!ft_strcmp(args[*i], "<<"))
	{
		red_here_doc(args, *i);
	}
}
