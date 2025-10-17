/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:38:11 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/10/17 19:45:50 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
