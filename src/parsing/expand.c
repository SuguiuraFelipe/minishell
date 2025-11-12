/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:50:49 by jde-carv          #+#    #+#             */
/*   Updated: 2025/11/12 18:34:09 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_status;

int	is_number(char c)
{
	return (c >= '0' && c <= '9');
}

static char	*expand_one_variable(char *line, char **envp, t_expand_class *ec)
{
	ec->start = ec->i + 1;
	while (ft_isalnum(line[ec->start]) || line[ec->start] == '_')
		ec->start++;
	ec->var_name = ft_substr(line, ec->i + 1, ec->start - ec->i - 1);
	ec->value = find_path_in_envp(envp, ec->var_name);
	free(ec->var_name);
	if (!ec->value)
		ec->value = "";
	line = get_suffix_and_prefix(line, *ec);
	ec->i = -1;
	return (line);
}

char	*expand_line_before_split(char *line, char **envp)
{
	t_expand_class	ec;
	int				qmode;

	line = ft_strdup(line);
	ec.i = 0;
	qmode = 0;
	while (line[ec.i])
	{
		qmode = update_qmode(qmode, line[ec.i]);
		if (line[ec.i] == '$' && line[ec.i + 1])
		{
			if (qmode != 1 && (ft_isalpha(line[ec.i + 1])
					|| line[ec.i + 1] == '_'))
				line = expand_one_variable(line, envp, &ec);
		}
		ec.i++;
	}
	return (line);
}
