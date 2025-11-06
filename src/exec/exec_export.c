/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:21:50 by jde-carv          #+#    #+#             */
/*   Updated: 2025/11/06 17:42:35 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*var_concatenation(char *s1, char *s2, char *s3)
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

static int	var_already_exist(char **dup_envp, char *var_name, char *new_var)
{
	int	j;
	int	len;

	len = ft_strlen(var_name);
	j = 0;
	while (dup_envp[j])
	{
		if (ft_strncmp(dup_envp[j], var_name, len) == 0
			&& dup_envp[j][len] == '=')
		{
			free(dup_envp[j]);
			dup_envp[j] = ft_strdup(new_var);
			return (1);
		}
		j++;
	}
	return (0);
}

/* Verifica se o nome da variável é válido (começa com letra ou '_') */
static int	is_valid_var_name(char *name)
{
	int	i;

	if (!isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	exec_export(char **args, char **dup_envp)
{
	int		i;
	int		j;
	char	*eq;
	char	*name;
	char	*raw_value;
	char	*clean_value;
	char	*final_entry;

	j = 0;
	i = 1;
	while (args[i])
	{
		eq = ft_strchr(args[i], '=');
		if (!eq)
			break ;
		*eq = '\0';
		name = args[i];
		if (!is_valid_var_name(name))
		{
			write(2, "minishell: export: `", 21);
			write(2, name, ft_strlen(name));
			write(2, "': not a valid identifier\n", 27);
			i++;
			continue ;
		}
		raw_value = eq + 1;
		clean_value = remove_quotes(raw_value);
		final_entry = var_concatenation(name, "=", clean_value);
		if (!var_already_exist(dup_envp, name, final_entry))
		{
			while (dup_envp[j])
				j++;
			dup_envp[j] = ft_strdup(final_entry);
			dup_envp[j + 1] = NULL;
		}
		free(clean_value);
		free(final_entry);
		i++;
	}
}
