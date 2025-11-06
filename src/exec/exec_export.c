/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:47:30 by jde-carv          #+#    #+#             */
/*   Updated: 2025/11/06 19:57:56 by jde-carv         ###   ########.fr       */
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

static void	extract_cmd(char **args, t_export_class *ec)
{
	while (args[ec->i + 1])
	{
		ec->temp = ft_strjoin(ec->joined, " ");
		free(ec->joined);
		ec->joined = ft_strjoin(ec->temp, args[ec->i + 1]);
		free(ec->temp);
		if (ft_strchr(args[ec->i + 1], '"') || ft_strchr(args[ec->i + 1], '\''))
			break;
		ec->i++;
	}
}
void	exec_export(char **args, char **dup_envp)
{
	t_export_class ec;

	ec.j = 0;
	ec.i = 1;
	while (args[ec.i])
	{
		ec.eq = ft_strchr(args[ec.i], '=');
		if (!ec.eq)
			break;
		*ec.eq = '\0';
		ec.name = args[ec.i];
		if (!check_identifier(ec.name) && (++ec.i || 1))
			continue;
		ec.raw_value = ec.eq + 1;
		ec.joined = ft_strdup(ec.raw_value);
		extract_cmd(args, &ec);
		ec.clean_value = remove_quotes(ec.joined);
		free(ec.joined);
		ec.final_entry = var_concatenation(ec.name, "=", ec.clean_value);
		free(ec.clean_value);
		if (!var_already_exist(dup_envp, ec.name, ec.final_entry))
			override_amb_value(dup_envp, ec);
		free(ec.final_entry);
		ec.i++;
	}
}
