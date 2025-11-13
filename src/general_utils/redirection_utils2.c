/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:31:17 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/11/13 20:38:27 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_quoted_token(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

int	validate_quote_token(char **args, int *i)
{
	if (is_quoted_token(args[*i]))
	{
		(*i)++;
		return (1);
	}
	return (0);
}

void	ft_remove_redirection_tokens(char **args, int start_index)
{
	int	j;

	if (args[start_index])
		free(args[start_index]);
	if (args[start_index + 1])
		free(args[start_index + 1]);
	j = start_index;
	while (args[j + 2])
	{
		args[j] = args[j + 2];
		j++;
	}
	args[j] = NULL;
	if (args[j + 1])
		args[j + 1] = NULL;
}
