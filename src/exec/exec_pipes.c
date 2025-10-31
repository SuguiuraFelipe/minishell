/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:29:42 by jde-carv          #+#    #+#             */
/*   Updated: 2025/10/31 19:17:16 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	has_pipe(char *s)
{
	int i;
	int has_pipe;

	i = 0;
	has_pipe = 0;
	while(s[i])
	{
		if(s[i] == '|')
		{
			has_pipe = 1;
			break;
		}
		i++;
	}
	return (has_pipe);
}
int count_pipes(char *s)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while(s[i])
	{
		if(s[i] == '|')
			count++;
		i++;
	}
	return (count);
}
