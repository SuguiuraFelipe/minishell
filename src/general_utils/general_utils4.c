/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 21:19:01 by jde-carv          #+#    #+#             */
/*   Updated: 2025/11/13 21:23:02 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	count_args_quoted(const char *s)
{
	int	i;
	int	count;
	int	qmode;

	i = 0;
	count = 0;
	qmode = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		if (!s[i])
			break ;
		count++;
		while (s[i])
		{
			qmode = update_qmode(qmode, s[i]);
			if (qmode == 0 && (s[i] == ' ' || s[i] == '\t'))
				break ;
			i++;
		}
	}
	return (count);
}

static char	*extract_one_arg(const char *s, int start)
{
	int		i;
	int		qmode;
	char	*tmp;
	char	*clean;

	i = start;
	qmode = 0;
	while (s[i])
	{
		qmode = update_qmode(qmode, s[i]);
		if (qmode == 0 && (s[i] == ' ' || s[i] == '\t'))
			break ;
		i++;
	}
	tmp = ft_substr(s, start, i - start);
	if (!tmp)
		return (NULL);
	clean = remove_quotes(tmp);
	free(tmp);
	return (clean);
}

static int	fill_one_arg(char **args, const char *s, int *i, int j)
{
	int	qmode;
	int	start;

	qmode = 0;
	start = *i;
	args[j] = extract_one_arg(s, start);
	if (!args[j])
		return (0);
	while (s[*i])
	{
		qmode = update_qmode(qmode, s[*i]);
		if (qmode == 0 && (s[*i] == ' ' || s[*i] == '\t'))
			break ;
		(*i)++;
	}
	return (1);
}

static int	fill_args_array(char **args, const char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		if (!s[i])
			break ;
		if (!fill_one_arg(args, s, &i, j))
			return (0);
		j++;
	}
	args[j] = NULL;
	return (1);
}

char	**split_args_with_quotes(const char *s)
{
	char	**args;
	int		count;

	if (!s)
		return (NULL);
	count = count_args_quoted(s);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	if (!fill_args_array(args, s))
	{
		free_split(args);
		return (NULL);
	}
	return (args);
}
