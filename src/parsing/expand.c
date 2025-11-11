/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:50:49 by jde-carv          #+#    #+#             */
/*   Updated: 2025/11/11 18:09:59 by fsuguiur         ###   ########.fr       */
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
			if (!ft_isalpha(result[i][1]) && result[i][1] != '_' && !is_number(result[i][1]))
				continue ;
			if (is_number(result[i][1]))
			{
				char *tmp = ft_strdup(result[i] + 2);
				free(result[i]);
				result[i] = tmp;
				continue ;
			}
			value = find_path_in_envp(envp, &result[i][1]);
			check_value(result, value, i);
		}
	}
}

char	*expand_line_before_split(char *line, char **envp)
{
	t_expand_class	ec;

	ec.i = 0;
	while (line[ec.i])
	{
		if (line[ec.i] == '$' && line[ec.i + 1] && (ft_isalpha(line[ec.i + 1])
				|| line[ec.i + 1] == '_'))
		{
			ec.start = ec.i + 1;
			while (ft_isalnum(line[ec.start]) || line[ec.start] == '_')
				ec.start++;
			ec.var_name = ft_substr(line, ec.i + 1, ec.start - ec.i - 1);
			ec.value = find_path_in_envp(envp, ec.var_name);
			free(ec.var_name);
			if (!ec.value)
				ec.value = "";
			get_suffix_and_prefix(line, ec);
			ec.i = -1;
		}
		ec.i++;
	}
	return (line);
}
