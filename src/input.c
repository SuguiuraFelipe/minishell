/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:37:26 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/10/16 17:45:43 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_status;

void	exit_minishell(void)
{
	write(1, "Exit\n", 5);
	exit(g_status);
}

int	has_non_blank_and_free(char **line_ptr)
{
	char	*line;
	size_t	i;

	if (!line_ptr || !*line_ptr)
		return (0);
	line = *line_ptr;
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0')
	{
		free(line);
		*line_ptr = NULL;
		return (0);
	}
	return (1);
}

int	quotes_balanced(const char *s)
{
	int in_single = 0;
	int in_double = 0;
	int i = 0;

	if (!s)
        return 1;
	while (s[i])
	{
		if (s[i] == '\'' && !in_double) 
            in_single = !in_single;
		else if (s[i] == '"' && !in_single) 
            in_double = !in_double;
		i++;
	}
	return (!in_single && !in_double);
}

char	*read_line_or_exit(void)
{
	char	*line;

	line = readline("$minishell ");
	if (line == NULL)
		exit_minishell();
	if (!has_non_blank_and_free(&line))
		return (NULL);
	if (!quotes_balanced(line))
	{
		fprintf(stderr, "minishell: unclosed quotes\n");
		free(line);
		return (NULL);
	}
	if (pipe_syntax_error(line))
	{
		fprintf(stderr, "minishell: syntax error near unexpected token `|'\n");
		free(line);
		return (NULL);
	}
	add_history(line);
	return (line);
}