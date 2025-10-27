/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 07:23:44 by jde-carv          #+#    #+#             */
/*   Updated: 2025/10/27 17:01:08 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int check_fail_red_simbol(char **args, int i, char *simbol)
{
    char *simbols[5];
    int j;
    
    j = 0;
    simbols[0] = ">";
    simbols[1] = ">>";
    simbols[2] = "<";
    simbols[3] = "<<";
    simbols[4] = NULL;
    if (!args[i + 1])
    {
        while (simbols[j])
        {
            if (!ft_strcmp(simbol, simbols[j]))
            {
                write(2, "minishell: syntax error near unexpected token `", 48);
                write(2, simbols[j], ft_strlen(simbols[j]));
                write(2, "'\n", 2);
                return (1);
            }
            j++;
        }
    }
    return (0);
}
static void red_in(char **args)
{
    int i = 0;
    int fd;

    if (check_fail_red_simbol(args, i, "<"))
        return;
    fd = open(args[i + 1], O_RDONLY);
    check_valid_fd(fd);
    dup2(fd, STDIN_FILENO);
    close(fd);
    int j = i;
    while (args[j + 2])
    {
        args[j] = args[j + 2];
        j++;
    }
    args[j] = NULL;
    args[j + 1] = NULL;
}
static void red_out(char **args)
{
    int i;
    int fd;

    i = 0;
    if (check_fail_red_simbol(args, i, ">"))
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
    int j = i;
    while (args[j + 2])
    {
        args[j] = args[j + 2];
        j++;
    }
        args[j] = NULL;
        args[j + 1] = NULL;
}

static void red_here_doc(char **args)
{
    int i = 0;
    int pipefd[2];
    char *line;

    while (args[i])
    {
        if (strcmp(args[i], "<<") == 0)
        {
            if (check_fail_red_simbol(args, i, "<<"))
                return;
            if (pipe(pipefd) < 0)
            {
                perror("pipe");
                return;
            }
            while (1)
            {
                line = readline("> ");
                if (!line || strcmp(line, args[i + 1]) == 0)
                    break;
                write(pipefd[1], line, strlen(line));
                write(pipefd[1], "\n", 1);
                free(line);
            }
            free(line);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
            close(pipefd[1]);
            int j = i;
            while (args[j + 2])
            {
                args[j] = args[j + 2];
                j++;
            }
            args[j] = NULL;
            args[j + 1] = NULL;
            break;
        }
        i++;
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
            red_in(&args[i++]);
        else if (ft_strcmp(args[i], ">>") == 0)
            red_out(&args[i++]);
        else if (ft_strcmp(args[i], "<") == 0)
            red_append(&args[i++]);
        else if (ft_strcmp(args[i], "<<") == 0)
            red_here_doc(&args[i++]);
        i++;
    }
}

