/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:12:58 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/10/28 17:40:23 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <signal.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# define MAX_DIR_SIZE 4096

typedef void		(*t_builtin_func)(char **args, char **envp);

typedef struct s_builtin_map
{
	char			*name;
	t_builtin_func	func;
}					t_builtin_map;

/*initalize map*/
void				init_builtin_map(t_builtin_map *builtins);

/* libft_utils */
void				*ft_memset(void *ptr, int value, size_t num);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strcat(char *dest, const char *src);
void				ft_bzero(void *s, size_t n);
size_t				ft_strlen(const char *s);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strchr(const char *str, int c);
size_t				ft_strlcpy(char *dest, const char *src, size_t dstsize);
char				*ft_strtrim(char const *s1, char const *set);
void				*ft_memcpy(void *dest, const void *src, size_t n);
char				*ft_strdup(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				**ft_split(char const *s, char c);
int					ft_strcmp(const char *s1, const char *s2);

/* general_utils */
void				do_not_return(int ac, char **av);
char				*cat_path_and_cmd(char *s1, char *s2, char *s3);
int					trim_parts(char **str_arr, const char *set);
void				free_split(char **v);
void				free_split_vector_only(char **str_arr);
void				ft_cmd_not_found(char *str);
char				*find_path_in_envp(char **envp, char *var_name);
char				*get_path(char *command, char **envp);
void				check_valid_fd(int fd);
void				ft_perror(char *s);

/* redirection utils */
int		check_fail_red_simbol(char **args, int i, char *simbol);
char    *set_here_doc_line(int *arr, char **args, int i);
void	dup_and_close_here_doc(int *arr);

/* parsing */
void				exit_minishell(void);
int					has_non_blank_and_free(char **line_ptr);
int					quotes_balanced(const char *s);
char				*read_line_or_exit(void);
void				change_pipe(char *s);
int					update_qmode(int qmode, char c);
char				*remove_space(char *line);
char				**parse_pipeline(char *line);
int					pipe_syntax_error(const char *s);
void				expand_amb_variables(char **envp, char **result);
char				*remove_quotes(char *s);
void				redirections(char **args);


/* builtin_utils */
int					is_builtin(char *s);
char				**dup_envp(char **envp);

/* exec */
void				exec_normal_commands(char **args, char **envp);
void				exec_commands(char **args, char **envp,
						t_builtin_map *builtins);
void				exec_cd(char **args, char **envp);
void				exec_pwd(char **args, char **envp);
void				exec_echo(char **args, char **dup_envp);
void				exec_exit(char **args, char **dup_envp);
void				exec_env(char **args, char **dup_envp);
void				exec_unset(char **args, char **dup_envp);
void				exec_export(char **args, char **dup_envp);

#endif