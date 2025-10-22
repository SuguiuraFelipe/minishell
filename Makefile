
NAME        := minishell
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g
INCLUDES    := -I.
LIBS        := -lreadline

SRCS        := src/main.c \
			   src/exec/normal_cmds.c \
			   src/exec/exec_cmds.c \
			   src/exec/exec_cd.c \
			   src/exec/exec_echo.c \
			   src/exec/exec_env.c \
			   src/exec/exec_exit.c \
			   src/exec/exec_export.c \
			   src/exec/exec_pwd.c \
			   src/exec/exec_unset.c \
 			   src/libft_utils/libft_utils.c \
 			   src/libft_utils/libft_utils2.c \
 			   src/libft_utils/libft_utils3.c \
 			   src/libft_utils/libft_utils4.c \
			   src/general_utils/builtins_utils.c \
			   src/general_utils/general_utils.c \
			   src/general_utils/get_path_utils.c \
			   src/parsing/input.c \
			   src/parsing/parse_pipeline.c

OBJS        := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
