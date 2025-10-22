/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:01:14 by devjorginho       #+#    #+#             */
/*   Updated: 2025/10/22 15:01:36 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_pwd(char **args, char **dup_envp)
{
	char *pwd_path;
	
	(void)args;
	pwd_path = ft_strdup(find_path_in_envp(dup_envp, "PWD"));
	printf("%s\n", pwd_path);
	free(pwd_path);
}
