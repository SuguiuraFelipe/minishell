/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:20:38 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/11/11 17:20:45 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_shlvl_index(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	normalize_shlvl_value(int lvl)
{
	if (lvl < 0)
		return (0);
	if (lvl >= 1000)
		return (1);
	return (lvl + 1);
}

void	update_shlvl(char **envp)
{
	int		i;
	int		lvl;
	char	*value;
	char	*new_value;
	char	*new_entry;

	i = get_shlvl_index(envp);
	if (i == -1)
	{
		envp[i + 1] = NULL;
		envp[i] = ft_strdup("SHLVL=1");
		return ;
	}
	value = envp[i] + 6;
	lvl = ft_atoi(value);
	lvl = normalize_shlvl_value(lvl);
	new_value = ft_itoa(lvl);
	new_entry = ft_strjoin("SHLVL=", new_value);
	free(new_value);
	free(envp[i]);
	envp[i] = new_entry;
}
