/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_normal_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 13:29:11 by devjorginho       #+#    #+#             */
/*   Updated: 2025/11/03 20:57:14 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char **check_sign_and_expand(char **args, char **envp)
{
    char *val;
    char *clean;

    if (!args || !args[0])
        return args;
    if (args[0][0] == '$')
    {
        val = find_path_in_envp(envp, args[0] + 1);
        if (!val)
            return NULL;
        clean = remove_quotes(val);
        return parse_pipeline(clean); 
    }
    return args;
}

void exec_normal_commands(char **args, char **envp)
{
    int pid;
    char *path;
    char **exec_args;

    if (!args || !args[0])
        return ;
    exec_args = check_sign_and_expand(args, envp);
    if (!exec_args)
        return ;
    path = get_path(exec_args[0], envp);
    if (!path)
    {
        ft_cmd_not_found(exec_args[0]);
        if (exec_args != args)
            free_split(exec_args);
        return ;
    }
    pid = fork();
    if (pid == 0)
    {
        redirections(exec_args);
        execve(path, exec_args, envp);
        perror("execve");
        exit(1);
    }
    else if (pid > 0)
        waitpid(pid, NULL, 0);
    else
        perror("fork");
    if (exec_args != args)
        free_split(exec_args);
    free(path);
}
