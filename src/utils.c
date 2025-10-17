/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:46:52 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/10/16 17:58:14 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	trim_parts(char **str_arr, const char *set)
{
	int		i;
	char	*t;

	if (!str_arr)
		return (0);
	i = 0;
	while (str_arr[i])
	{
		t = ft_strtrim(str_arr[i], set);
		if (!t)
			return (0);
		free(str_arr[i]);
		str_arr[i] = t;
		i++;
	}
	return (1);
}

void	free_split(char **str_arr)
{
	int	i;

	if (!str_arr)
		return ;
	i = 0;
	while (str_arr[i])
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
}

void	free_split_vector_only(char **str_arr)
{
	free(str_arr);
}
