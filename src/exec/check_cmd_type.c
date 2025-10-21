/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:51:09 by devjorginho       #+#    #+#             */
/*   Updated: 2025/10/21 12:02:40 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_builtin(char *s)
{
	if (!s)
		return (0);
	return (!ft_strcmp(s, "echo")
		|| !ft_strcmp(s, "cd")
		|| !ft_strcmp(s, "pwd")
		|| !ft_strcmp(s, "export")
		|| !ft_strcmp(s, "unset")
		|| !ft_strcmp(s, "env")
		|| !ft_strcmp(s, "exit"));
}
