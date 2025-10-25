/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:50:49 by jde-carv          #+#    #+#             */
/*   Updated: 2025/10/25 17:38:10 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//char *expand_amb_variables(char **envp, char **result)
//{
//	int i;
//	int j;
//	int len = 0;
//	char *amb_path = NULL;

//	j = 0;
//	i = 0;
//	while(result[i])
//	{
//		if(result[i][0] == '$')
//		{
//			len = ft_strlen(find_path_in_envp(envp, &result[i][1]));
//			amb_path = malloc(sizeof(char) * len + 1);
//		}
//		while(j < len)
//		{
//			amb_path[j] = find_path_in_envp(envp, &result[i][1])[j];
//			j++;
//		}
//		result[i] = ft_strdup(amb_path);
//		free(amb_path);
//		i++;
//		return (*result);
//	}
//	return NULL;
//}

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

