/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 07:23:44 by jde-carv          #+#    #+#             */
/*   Updated: 2025/11/03 20:26:04 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void check_file_is_dir(const char *path)
{
    struct stat status;

    if (stat(path, &status) == 0 && S_ISDIR(status.st_mode))
    {
        write(2, "minishell: ", 11);
        write(2, path, ft_strlen(path));
        write(2, ": is a directory\n", 17);
        errno = EISDIR;
        return;
    }
}

static int red_in(char **args)
{
    int i;
    int fd;

    i = 0;
    if (check_fail_red_simbol(args, i, "<"))
        return -1;
    check_file_is_dir(args[i + 1]);
    if (errno == EISDIR)
        return -1;
    fd = open(args[i + 1], O_RDONLY);
    if (fd == -1)
        return -1;
    dup2(fd, STDIN_FILENO);
    close(fd);
    args[i] = NULL;
    args[i + 1] = NULL;
    return 0;
}

static int red_out(char **args)
{
    int i;
    int fd;

    i = 0;
    if (check_fail_red_simbol(args, i, ">"))
        return -1;
    check_file_is_dir(args[i + 1]);
    if (errno == EISDIR)
        return -1;
    fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return -1;
    dup2(fd, STDOUT_FILENO);
    close(fd);
    args[i] = NULL;
    args[i + 1] = NULL;
    return 0;
}

static int red_append(char **args)
{
    int i;
    int fd;

    i = 0;
    if (check_fail_red_simbol(args, i, ">>"))
        return -1;
    check_file_is_dir(args[i + 1]);
    if (errno == EISDIR)
        return -1;
    fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
        return -1;
    dup2(fd, STDOUT_FILENO);
    close(fd);
    args[i] = NULL;
    args[i + 1] = NULL;
    return 0;
}

static void red_here_doc(char **args)
{
    int i;
    int j;
    int pipefd[2];

    i = -1;
    while (args[++i])
    {
        if (ft_strcmp(args[i], "<<") == 0)
        {
            if (check_fail_red_simbol(args, i, "<<"))
                return;
            if (pipe(pipefd) < 0)
                ft_perror("pipe");
            set_here_doc_line(pipefd, args, i);
            dup_and_close_here_doc(pipefd);
            j = i - 1;
            while (args[(++j) + 2])
                args[j] = args[j + 2];
            args[j] = NULL;
            args[j + 1] = NULL;
            break;
        }
    }
}

int redirections(char **args)
{
    int i;
    int error;

    i = 0;
    error = 0;
    while (args[i])
    {
        if (!args[i + 1])
            break;
        if (ft_strcmp(args[i], ">") == 0 && red_out(&args[i++]) == -1)
            error = 1;
        else if (ft_strcmp(args[i], ">>") == 0 && red_append(&args[i++]) == -1)
            error = 1;
        else if (ft_strcmp(args[i], "<") == 0 && red_in(&args[i++]) == -1)
            error = 1;
        else if (ft_strcmp(args[i], "<<") == 0)
            red_here_doc(&args[i++]);
        i++;
    }
    if (error)
        return -1;
    return 0;
}

