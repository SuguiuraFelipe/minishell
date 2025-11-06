/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:53:20 by jde-carv          #+#    #+#             */
/*   Updated: 2025/11/06 19:53:28 by jde-carv         ###   ########.fr       */
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