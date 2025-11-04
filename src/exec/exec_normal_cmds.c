/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_normal_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 08:41:47 by devjorginho       #+#    #+#             */
/*   Updated: 2025/11/04 17:04:45 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

static void	init_and_check_execve(int pid, char *path, char **args, char **envp)
{
    if (pid == 0)
    {
        execve(path, args, envp);
        perror("execve");
        exit(1); 
    }
    else if (pid > 0)
    {
        int status;
        
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            g_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            g_status = 128 + WTERMSIG(status);
    }
    else
    {
        perror("fork");
        g_status = 1; 
    }
}

void    exec_normal_commands(char **args, char **envp, int original_stdin_fd)
{
    int     pid;
    char    *path;
    int     red_res;

    if (!args || !args[0])
        return ;
    red_res = redirections(args);
    if (red_res == -1 || !args[0])
    {
        dup2(original_stdin_fd, STDIN_FILENO); 
        return ;
    }
    path = get_path(args[0], envp);
    if (!path)
    {
        ft_cmd_not_found(args[0]);
        dup2(original_stdin_fd, STDIN_FILENO);
        return ;
    }
    pid = fork();
    init_and_check_execve(pid, path, args, envp);
    dup2(original_stdin_fd, STDIN_FILENO);
    free(path);
}
