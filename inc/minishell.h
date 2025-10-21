/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:12:58 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/10/21 12:15:46 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

/* libft_utils */
void	*ft_memset(void *ptr, int value, size_t num);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strchr(const char *str, int c);
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);
char	*ft_strtrim(char const *s1, char const *set);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strdup(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	**ft_split(char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);

/* general_utils */
void	free_split(char **v);
int		trim_parts(char **str_arr, const char *set);
void	free_split_vector_only(char **str_arr);
char	*cat_path_and_cmd(char *s1, char *s2, char *s3);

/* parsing */
void	exit_minishell(void);
int		has_non_blank_and_free(char **line_ptr);
int		quotes_balanced(const char *s);
char	*read_line_or_exit(void);
void	change_pipe(char *s);
int		update_qmode(int qmode, char c);
char 	*remove_space(char *line);
char 	**parse_pipeline(char *line);
int		pipe_syntax_error(const char *s);

/* exec */
int		is_builtin(char *s);
void	exec_normal_commands(char **args, char **envp);


#endif