/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:58:37 by jde-carv          #+#    #+#             */
/*   Updated: 2025/11/13 19:55:46 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern int			g_status;

# define MAX_DIR_SIZE 4096

typedef void		(*t_builtin_func)(char **args, char **envp);

typedef struct s_builtin_map
{
	char			*name;
	t_builtin_func	func;
}					t_builtin_map;

typedef struct s_data_pipes
{
	int				**pipes;
	int				original_stdin_fd;
	int				ncmds;
	pid_t			*pids;
}					t_data_pipes;

typedef struct s_expand_class
{
	int				i;
	int				j;
	char			*eq;
	char			*name;
	char			*raw_value;
	char			*joined;
	char			*temp;
	char			*clean_value;
	char			*final_entry;
}					t_export_class;

typedef struct t_expand_class
{
	int				i;
	int				start;
	char			*var_name;
	char			*value;
	char			*prefix;
	char			*suffix;
	char			*expanded;

}					t_expand_class;

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
void				ft_putstr_fd(char *str, int fd);
int					ft_atoi(const char *str);
char				*ft_substr(const char *s, unsigned int start, size_t len);
char				*ft_itoa(int n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					is_letter(char c);
int					ft_isdigit(int c);

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
void				check_file_is_dir(const char *path);
void				handle_exec_error(char *cmd);
int					check_identifier(char *name);
void				override_amb_value(char **dup_envp, t_export_class ec);
char				*get_suffix_and_prefix(char *line, t_expand_class ec);
int					is_quoted_token(char *arg);

/* redirection utils */
int					check_fail_red_simbol(char **args, int i, char *simbol);
char				*set_here_doc_line(int *arr, char **args, int i);
void				dup_and_close_here_doc(int *arr);
int					free_here_doc(char **args, int i, char *simbol);
void				check_redirection(char **args, int *i, int *error);
int					red_in(char **args, int i);
int					red_out(char **args, int i);
int					red_append(char **args, int i);
void				red_here_doc(char **args, int i);

/* parsing */
void				exit_minishell(void);
int					has_non_blank_and_free(char **line_ptr);
int					quotes_balanced(const char *s);
char				*read_line_or_exit(void);
void				change_pipe(char *s);
int					update_qmode(int qmode, char c);
char				**parse_pipeline(char *line);
int					pipe_syntax_error(const char *s);
char				*remove_quotes(char *s);
int					redirections(char **args);
int					is_pipeline(char **args);
void				dispatch(char **args, char **envp, t_builtin_map *builtins,
						int original_stdin_fd);
void				exec_single(char *str, char **envp, t_builtin_map *builtins,
						int original_stdin_fd);
void				exec_pipeline(char **args, char **envp,
						t_builtin_map *builtins, int original_stdin_fd);
void				free_all_pipes(int **pipes, int ncmds);
int					count_cmds(char **args);
int					**create_pipes(int ncmds);
void				close_all_pipes(int **pipes, int ncmds);
void				setup_child_fds(int i, int ncmds, int **pipes);
void				update_shlvl(char **envp);
char				*expand_line_before_split(char *line, char **envp);

/* builtin_utils */
int					is_builtin(char *s);
int					is_broken_end(const char *s);
int					is_broken_start(const char *s);
char				**dup_envp(char **envp);
char				*safe_strjoin(char *s1, const char *s2);
void 				ft_remove_redirection_tokens(char **args, int start_index);

/* exec */
void				exec_normal_commands(char **args, char **envp,
						int original_stdin_fd);
void				exec_commands(char **args, char **envp,
						t_builtin_map *builtins, int original_stdin_fd);
void				exec_cd(char **args, char **envp);
void				exec_pwd(char **args, char **envp);
void				exec_echo(char **args, char **dup_envp);
void				exec_exit(char **args, char **dup_envp);
void				exec_env(char **args, char **dup_envp);
void				exec_unset(char **args, char **dup_envp);
void				exec_export(char **args, char **dup_envp);
int					has_pipe(char *s);
int					count_pipes(char *s);

#endif