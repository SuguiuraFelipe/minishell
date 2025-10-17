/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 20:33:48 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/10/17 18:57:21 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int g_status = 0;

int	main(void)
{
	char	*line;
    char    **result;
	int		i;

	while (1)
	{
        line = read_line_or_exit();
		if (!line)
        continue ;
		result = parse_pipeline(line);
		if (!result)
			continue ;
		i = 0;
		while (result[i])
		{
			printf("cmd[%d]: «%s»\n", i, result[i]);
            i++;
		}
	}
	return (0);
}


