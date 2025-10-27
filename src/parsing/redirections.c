/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 07:23:44 by jde-carv          #+#    #+#             */
/*   Updated: 2025/10/27 17:59:51 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void red_in(char **args)
{
    int i = 0;
    int fd;

    if (check_fail_red_simbol(args, i, ">"))
        return;
    fd = open(args[i + 1], O_RDONLY);
    check_valid_fd(fd);
    dup2(fd, STDIN_FILENO);
    close(fd);
    int j = i;
    args[j] = NULL;
    args[j + 1] = NULL;
}
static void red_out(char **args)
{
    int i;
    int fd;

    i = 0;
    if (check_fail_red_simbol(args, i, "<"))
        return;
    fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    check_valid_fd(fd);
    dup2(fd, STDOUT_FILENO);
    close(fd);
    args[i] = NULL;
    args[i + 1] = NULL;
}

static void red_append(char **args)
{
    int i;
    int fd;

    i = 0;
    if (check_fail_red_simbol(args, i, ">>"))
        return;
    fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    check_valid_fd(fd);
    dup2(fd, STDOUT_FILENO);
    close(fd);
    args[i] = NULL;
    args[i + 1] = NULL;
}

// falta funcionar direito sem argumentos de comandos passando << como primeiro argumento
// precisa nao aparecer erro do execve 
// precisa tirar o Bad address pois nao existe no bash original

static void red_here_doc(char **args)
{
    int i;
    int j;
    int pipefd[2];
    char *line;

    i = -1;
    while (args[++i])
    {
        if (strcmp(args[i], "<<") == 0)
        {
            if (check_fail_red_simbol(args, i, "<<"))
                return;
            if (pipe(pipefd) < 0)
                ft_perror("pipe");
            line = set_here_doc_line(pipefd, args, i);
            dup_and_close_here_doc(pipefd);
            j = (i - 1);
            while (args[(++j) + 2])
                args[j] = args[j + 2];
            args[j] = NULL;
            args[j + 1] = NULL;
            break;
        }
    }
}
void redirections(char **args)
{
    int i;

    i = 0;
    while (args[i])
    {
        if (!args[i + 1])
            break;
        if (ft_strcmp(args[i], ">") == 0)
            red_out(&args[i++]);
        else if (ft_strcmp(args[i], ">>") == 0)
            red_append(&args[i++]);
        else if (ft_strcmp(args[i], "<") == 0)
            red_in(&args[i++]);
        else if (ft_strcmp(args[i], "<<") == 0)
            red_here_doc(&args[i++]);
        i++;
    }
}

