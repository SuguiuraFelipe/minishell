/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:59:30 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/10/24 18:56:47 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	should_copy_char(char c, int modo)
{
	if (c == '\'' && modo != 2)
		return (0);
	if (c == '"' && modo != 1)
		return (0);
	return (1);
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

char	*remove_quotes(char *s)
{
	int		i;
	int		j;
	int		modo;
	char	*resultado;

	if (!s)
		return (NULL);
	resultado = malloc(strlen(s) + 1);
	if (!resultado)
		return (NULL);
	i = 0;
	j = 0;
	modo = 0;
	while (s[i])
	{
		modo = update_qmode(modo, s[i]);
		if (should_copy_char(s[i], modo))
		{
			resultado[j] = s[i];
			j++;
		}
		i++;
	}
	resultado[j] = '\0';
	return (resultado);
}
