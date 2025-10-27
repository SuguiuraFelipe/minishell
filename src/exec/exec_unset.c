/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:02:51 by devjorginho       #+#    #+#             */
/*   Updated: 2025/10/27 07:42:13 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_unset(char **args, char **dup_envp)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (args[++i])
	{
		j = -1;
		len = ft_strlen(args[i]);
		while (dup_envp[++j])
		{
			if (ft_strncmp(dup_envp[j], args[i], len) == 0
				&& dup_envp[j][len] == '=')
			{
				free(dup_envp[j]);
				while (dup_envp[j + 1])
				{
					dup_envp[j] = dup_envp[j + 1];
					j++;
				}
				dup_envp[j] = NULL;
				break ;
			}
		}
	}
}
