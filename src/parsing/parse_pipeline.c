/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:38:11 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/11/04 17:05:13 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	change_pipe(char *s)
{
	int	i;
	int	q;

	if (!s)
		return ;
	i = 0;
	q = 0;
	while (s[i])
	{
		q = update_qmode(q, s[i]);
		if (q == 0 && s[i] == '|')
			s[i] = '\2';
		i++;
	}
}
char	**parse_pipeline(char *line)
{
	char	**parts;

	if (!line)
		return (NULL);
	change_pipe(line);
	parts = ft_split(line, '\2');
	if (!parts)
		return (NULL);
	if (!trim_parts(parts, " \t\n\r"))
	{
		free_split(parts);
		return (NULL);
	}
	return (parts);
}

int	pipe_syntax_error(const char *s)
{
	size_t	i;
	int		q;
	int		need;

	i = 0;
	q = 0;
	need = 1;
	while (s && s[i])
	{
		char	c;

		c = s[i++];
		q = update_qmode(q, c);
		if (q == 0 && (c == ' ' || c == '\t'))
			continue ;
		if (q == 0 && c == '|')
		{
			if (need)
				return (1);
			need = 1;
			continue ;
		}
		need = 0;
	}
	return (need != 0);
}
