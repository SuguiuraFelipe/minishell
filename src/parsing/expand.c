/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:50:49 by jde-carv          #+#    #+#             */
/*   Updated: 2025/10/27 07:43:48 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expand_amb_variables(char **envp, char **result)
{
	int i;
	char *value;

	i = 0;
	while (result[i])
	{
		if (result[i][0] == '$' && result[i][1])
		{
			value = find_path_in_envp(envp, &result[i][1]);
			if (value)
			{
				free(result[i]);
				result[i] = ft_strdup(value);
			}
			else
			{
				free(result[i]);
				result[i] = ft_strdup("");
			}
		}
		i++;
	}
}

