/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:38:11 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/10/24 19:03:09 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	change_pipe(char *s)
{
	int i = 0;
	int q = 0;

	while (s[i])
	{
		q = update_qmode(q, s[i]);
		if (s[i] == '|' && q == 0)
			s[i] = '\2';
		i++;
	}
}

static char *tokenize_arguments(char *line)
{
    char    *result;
    int     i = 0;
    int     j = 0;
    int     qmode = 0;

    if (!line)
        return (NULL);
    result = malloc(strlen(line) + 1);
    if (!result)
        return (NULL);
    while (line[i])
    {
        qmode = update_qmode(qmode, line[i]);
        if (qmode == 0 && (line[i] == ' ' || line[i] == '\t'))
        {
            while (line[i] && (line[i] == ' ' || line[i] == '\t'))
                i++;
            if (i > 0)
                result[j++] = '\2';
            continue ;
        }
        result[j++] = line[i++];
    }
    result[j] = '\0';
    return (result);
}

char **parse_pipeline(char *line)
{
	char	*tmp;
	char 	*result;
	char	**parts;
	int	i;

	i = 0;
	change_pipe(line);
	result = tokenize_arguments(line);
	parts = ft_split(result, '\2');
	free(result);
	if (!parts)
		return (NULL);
	if (!trim_parts(parts, " \t"))
	{
		free_split(parts);
		return (NULL);
	}
	while (parts[i])
	{
		tmp = remove_quotes(parts[i]);
		free(parts[i]);
		parts[i] = tmp;
		i++;
	}
	return (parts);
}
int	pipe_syntax_error(const char *s)
{
	size_t	i = 0;
	int		q = 0;
	int		need = 1;

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
