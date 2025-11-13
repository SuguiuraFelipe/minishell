/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:40:08 by jde-carv          #+#    #+#             */
/*   Updated: 2025/11/13 17:57:39 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_broken_start(const char *s)
{
	int	result;

	if (!s || ft_strlen(s) < 1)
		return (0);
	result = (s[0] == '"' && ft_strchr(s, '\''));
	return (result);
}

int	is_broken_end(const char *s)
{
	size_t	len;
	int		result;
	int		len_is_valid;

	len_is_valid = ((len = ft_strlen(s)) < 1);
	if (!s || len_is_valid)
		return (0);
	result = (s[len - 1] == '"' && ft_strchr(s, '\''));
	return (result);
}

char	*safe_strjoin(char *s1, const char *s2)
{
	char	*new_s;

	if (!s1)
		return (ft_strdup(s2));
	new_s = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!new_s)
	{
		free(s1);
		return (NULL);
	}
	ft_strcpy(new_s, s1);
	ft_strcat(new_s, " ");
	ft_strcat(new_s, s2);
	free(s1);
	return (new_s);
}
