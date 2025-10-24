/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:59:30 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/10/24 18:08:35 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	quotes_mode(int modo, char c)
{
	if (c == '\'' && modo != 2)
	{
		if (modo == 1)
			return (0);
		return (1);
	}
	if (c == '"' && modo != 1)
	{
		if (modo == 2)
			return (0);
		return (2);
	}
	return (modo);
}

static int	should_copy_char(char c, int modo)
{
	if (c == '\'' && modo != 2)
		return (0);
	if (c == '"' && modo != 1)
		return (0);
	return (1);
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
		modo = quotes_mode(modo, s[i]);
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
