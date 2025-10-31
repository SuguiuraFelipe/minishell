/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:38:11 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/10/31 20:11:57 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** update_qmode() está em quotes.c
** 0 = fora de aspas
** 1 = dentro de '
** 2 = dentro de "
*/

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

/*
** Devolve:
**  "echo hello | cat | cat"
**  -> ["echo hello", "cat", "cat", NULL]
**
** NÃO quebra por espaço. NÃO remove aspas.
** Só separa os blocos do pipeline e tira espaços/\t/\n/\r das pontas.
*/
char	**parse_pipeline(char *line)
{
	char	**parts;

	if (!line)
		return (NULL);
	change_pipe(line);
	parts = ft_split(line, '\2');
	if (!parts)
		return (NULL);
	/* aqui estava o problema: limpar também \n e \r */
	if (!trim_parts(parts, " \t\n\r"))
	{
		free_split(parts);
		return (NULL);
	}
	return (parts);
}

/*
** usado no input.c para rejeitar "||" e pipe no início/fim
*/
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
