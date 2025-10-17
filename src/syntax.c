/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:09:07 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/10/16 17:11:55 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

