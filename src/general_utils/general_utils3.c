/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:53:20 by jde-carv          #+#    #+#             */
/*   Updated: 2025/11/12 17:50:40 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	override_amb_value(char **dup_envp, t_export_class ec)
{
	while (dup_envp[ec.j])
		ec.j++;
	dup_envp[ec.j] = ft_strdup(ec.final_entry);
	dup_envp[ec.j + 1] = NULL;
}

char	*get_suffix_and_prefix(char *line, t_expand_class ec)
{
	char	*prefix;
	char	*suffix;
	char	*temp;
	char	*new_line;

	prefix = ft_substr(line, 0, ec.i);
	suffix = ft_strdup(&line[ec.start]);
	temp = ft_strjoin(prefix, ec.value);
	new_line = ft_strjoin(temp, suffix);
	free(prefix);
	free(suffix);
	free(temp);
	free(line);
	return (new_line);
}
