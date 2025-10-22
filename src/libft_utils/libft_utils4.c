/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:50:40 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/10/22 12:53:18 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_strlen_sep(char const *str, char c, int i)
{
	int	count;

	count = 0;
	while (str[i] != c && str[i])
	{
		count++;
		i++;
	}
	return (count + 1);
}

static int	word_count(char const *str, char c)
{
	int	i;
	int	word_count;

	i = 0;
	word_count = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != c && str[i])
		{
			word_count++;
			while (str[i] != c && str[i])
			{
				i++;
			}
		}
	}
	return (word_count + 1);
}

static int	add_word(char const *str, char **word, int i, char c)
{
	int	k;

	*word = (char *) malloc(ft_strlen_sep(str, c, i));
	if (!*word)
		return (i);
	k = 0;
	while (str[i] != c && str[i])
	{
		(*word)[k++] = str[i++];
	}
	(*word)[k] = '\0';
	return (i);
}

static char	**check_null(char **ptr, int j)
{
	while (j-- > 0)
		free(ptr[j]);
	free(ptr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**str_arr;

	str_arr = (char **) malloc (word_count(s, c) * (sizeof(char *)));
	if (!str_arr)
		return (str_arr);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			i = add_word(s, &str_arr[j], i, c);
			if (!str_arr[j])
			{
				return (check_null(str_arr, j));
			}
			j++;
		}
	}
	str_arr[j] = NULL;
	return (str_arr);
}
