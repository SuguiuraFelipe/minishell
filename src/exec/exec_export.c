/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:03:11 by devjorginho       #+#    #+#             */
/*   Updated: 2025/11/06 17:14:58 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:03:11 by devjorginho       #+#    #+#             */
/*   Updated: 2025/11/06 19:18:42 by jde-carv         ###   ########.fr       */
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

static int	dont_have_value(char *var_value, int i)
{
	(void)i;
	if (!var_value)
	{
		i++;
		return (1);
	}
	return (0);
}

/*
** Exporta variáveis de ambiente no formato NAME=VALUE
** - Remove aspas do VALUE ("ls -l" → ls -l)
** - Substitui variáveis já existentes
*/
void	exec_export(char **args, char **dup_envp)
{
	int		i;
	int		j;
	char	*var_name;
	char	*var_value;
	char	*clean_value;
	char	*new_entry;

	j = 0;
	i = 1;
	while (args[i])
	{
		var_value = ft_strchr(args[i], '=');
		if (dont_have_value(var_value, i))
			break ;
		*var_value = '\0';
		var_name = args[i];
		var_value++;
		clean_value = remove_quotes(var_value);
		new_entry = var_concatenation(var_name, "=", clean_value);
		if (!var_already_exist(dup_envp, var_name, new_entry))
		{
			while (dup_envp[j])
				j++;
			dup_envp[j] = ft_strdup(new_entry);
			dup_envp[j + 1] = NULL;
		}
		free(clean_value);
		free(new_entry);
		i++;
	}
}
