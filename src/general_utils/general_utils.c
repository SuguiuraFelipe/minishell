/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:46:52 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/10/21 11:31:14 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*cat_path_and_cmd(char *s1, char *s2, char *s3)
{
	char	*temp;
	char	*result;

	if (!s1 || !s2 || !s3)
		return (NULL);
	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, s3);
	free(temp);
	return (result);
}

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

