/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:50:49 by jde-carv          #+#    #+#             */
/*   Updated: 2025/11/06 16:22:40 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_status;

static int	expand_exit_status(char **simbol)
{
	char	*status_str;

	if ((*simbol)[1] == '?' && !(*simbol)[2])
	{
		status_str = ft_itoa(g_status);
		free(*simbol);
		*simbol = status_str;
		return (1);
	}
	return (0);
}

static void	check_value(char **result, char *value, int i)
{
	if (value)
	{
		free(result[i]);
		result[i] = ft_strdup(value);
	}
	else
	{
		free(result[i]);
		result[i] = ft_strdup("");
	}
}

int	is_number(char c)
{
	return (c >= '0' && c <= '9');
}

void	expand_amb_variables(char **envp, char **result)
{
	int		i;
	char	*value;

	i = -1;
	while (result[++i])
	{
		if (result[i][0] == '$' && result[i][1])
		{
			if (expand_exit_status(&result[i]))
				continue ;
			value = find_path_in_envp(envp, &result[i][1]);
			check_value(result, value, i);
		}
	}
}
