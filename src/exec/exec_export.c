/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:03:11 by devjorginho       #+#    #+#             */
/*   Updated: 2025/11/06 18:54:35 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	exec_export(char **args, char **dup_envp)
{
	int		i;
	int		j;
	char	*eq;
	char	*name;
	char	*raw_value;

	j = 0;
	i = 1;
	while (args[i])
	{
		eq = ft_strchr(args[i], '=');
		if (!eq)
			break;
		*eq = '\0';
		name = args[i];
		if (!isalpha(name[0]) && name[0] != '_')
		{
			write(2, "minishell: export: `", 21);
			write(2, name, ft_strlen(name));
			write(2, "': not a valid identifier\n", 27);
			i++;
			continue;
		}
		raw_value = eq + 1;

		// 🔹 Junta partes até achar fechamento das aspas
		char *joined = ft_strdup(raw_value);
		while (args[i + 1])
		{
			char *temp = ft_strjoin(joined, " ");
			free(joined);
			joined = ft_strjoin(temp, args[i + 1]);
			free(temp);
			if (ft_strchr(args[i + 1], '"') || ft_strchr(args[i + 1], '\''))
				break;
			i++;
		}

		// 🔹 Remove aspas
		char *clean_value = remove_quotes(joined);
		free(joined);

		// 🔹 Monta entrada final VAR=VALOR
		char *final_entry = var_concatenation(name, "=", clean_value);
		free(clean_value);

		if (!var_already_exist(dup_envp, name, final_entry))
		{
			while (dup_envp[j])
				j++;
			dup_envp[j] = ft_strdup(final_entry);
			dup_envp[j + 1] = NULL;
		}
		free(final_entry);
		i++;
	}
}

