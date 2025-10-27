/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:22:16 by jde-carv          #+#    #+#             */
/*   Updated: 2025/10/27 17:53:47 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int check_fail_red_simbol(char **args, int i, char *simbol)
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

char    *set_here_doc_line(int *arr, char **args, int i)
{
    char *line;
    while (1)
    {
        line = readline("> ");
        if (!line || strcmp(line, args[i + 1]) == 0)
            break;
        write(arr[1], line, strlen(line));
        write(arr[1], "\n", 1);
        free(line);
    }
    return (line);
}
void dup_and_close_here_doc(int *arr)
{
    dup2(arr[0], STDIN_FILENO);
    close(arr[0]);
    close(arr[1]);
}