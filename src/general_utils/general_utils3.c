/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:53:20 by jde-carv          #+#    #+#             */
/*   Updated: 2025/11/13 20:49:15 by jde-carv         ###   ########.fr       */
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

void	path_is_not_valid(char **args, int original_stdin_fd,
		int original_stdout_fd)
{
	ft_cmd_not_found(args[0]);
	dup2(original_stdin_fd, STDIN_FILENO);
	dup2(original_stdout_fd, STDOUT_FILENO);
	close(original_stdout_fd);
}

void	redirect_is_not_valid(int original_stdin_fd, int original_stdout_fd)
{
	dup2(original_stdin_fd, STDIN_FILENO);
	dup2(original_stdout_fd, STDOUT_FILENO);
	close(original_stdout_fd);
}
