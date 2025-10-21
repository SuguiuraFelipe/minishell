/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:38:11 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/10/21 11:45:59 by devjorginho      ###   ########.fr       */
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

int	update_qmode(int qmode, char c)
{
	if (c == '\'' && qmode != 2)
	{
		if (qmode == 1)
			return (0);
		else
			return (1);
	}
	if (c == '"' && qmode != 1)
	{
		if (qmode == 2)
			return (0);
		else
			return (2);
	}
	return (qmode);
}

char *remove_space(char *line)
{
    int i = 0;
    int k = 0;
    char *result;

    if (!line)
        return (NULL);
    result = malloc(strlen(line) + 1);
    if (!result)
        return (NULL);

    while (line[i])
    {
        if (line[i] == ' ' && line[i + 1] && line[i + 1] != ' ' && i > 0 
			&& line[i - 1] != ' ')
        {
            result[k++] = '\2';
            i++;
            continue;
        }
        result[k++] = line[i++];
    }
    result[k] = '\0';
    return (result);
}


char **parse_pipeline(char *line)
{
	char 	*result;
	char	**parts;

	change_pipe(line);
	result = remove_space(line);
	parts = ft_split(result, '\2');
	free(result);
	if (!parts)
		return (NULL);
	if (!trim_parts(parts, " \t"))
	{
		free_split(parts);
		return (NULL);
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
