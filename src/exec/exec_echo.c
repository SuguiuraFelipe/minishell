/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:27:18 by jde-carv          #+#    #+#             */
/*   Updated: 2025/11/13 16:33:37 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../inc/minishell.h"

static int is_broken_start(const char *s)
{
    if (!s || ft_strlen(s) < 1)
        return (0);
    return (s[0] == '"' && ft_strchr(s, '\'')); 
}

static int is_broken_end(const char *s)
{
    size_t len;

    if (!s || (len = ft_strlen(s)) < 1)
        return (0);
    return (s[len - 1] == '"' && ft_strchr(s, '\''));
}

static char *safe_strjoin(char *s1, const char *s2)
{
    char *new_s;

    if (!s1)
        return (ft_strdup(s2));
    new_s = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
    if (!new_s)
    {
        free(s1);
        return (NULL);
    }
    ft_strcpy(new_s, s1);
    ft_strcat(new_s, " ");
    ft_strcat(new_s, s2);
    free(s1);
    return (new_s);
}
static int is_valid_n_flag(const char *s)
{
    int i;

    if (!s || ft_strlen(s) < 2 || s[0] != '-' || s[1] != 'n')
        return (0);
    i = 2;
    while (s[i])
    {
        if (s[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

void    exec_echo(char **args, char **envp)
{
    int     i;
    int     j;
    int     print_newline;
    char    *clean;
    char    *temp_arg;
    
    (void)envp;
    i = 1;
    print_newline = 1;
    while (args[i] && is_valid_n_flag(args[i]))
    {
        print_newline = 0;
        i++;
    }
    while (args[i])
    {
        if (is_broken_start(args[i]) && args[i + 1])
        {
            clean = ft_strdup(args[i]);
            if (!clean)
                return;
            j = i + 1;
            while (args[j] && !is_broken_end(args[j]))
            {
                clean = safe_strjoin(clean, args[j]);
                if (!clean)
                    return;
                j++;
            }
            if (args[j] && is_broken_end(args[j]))
            {
                clean = safe_strjoin(clean, args[j]);
                if (!clean)
                    return;
                i = j;
            }
        }
        else
        {
            clean = ft_strdup(args[i]);
            if (!clean)
                return;
        }
        temp_arg = remove_quotes(clean);
        free(clean);
        ft_putstr_fd(temp_arg, 1);
        if (args[i + 1]) 
            ft_putstr_fd(" ", 1);

        free(temp_arg);
        i++;
    }
    if (print_newline)
        ft_putstr_fd("\n", 1);
}
