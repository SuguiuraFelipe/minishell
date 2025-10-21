/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 20:33:48 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/10/21 12:22:58 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int g_status = 0;

int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	char	*line;
    char    **result;

	while (1)
	{
    	line = read_line_or_exit();
    	if (!line)
        	continue ;
    	result = parse_pipeline(line);
   		if (!result)
        	continue ;
		if(!is_builtin(result[0]))
    		exec_normal_commands(result, envp);
		else
			printf("Coreano safado !\n");
    	//free_tokens(result);
    	free(line);
	}
	return (0);
}


