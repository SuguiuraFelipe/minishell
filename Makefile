
NAME        := minishell
CC          := cc
CFLAGS      := -Wall -Wextra -Werror
INCLUDES    := -I.
LIBS        := -lreadline

SRCS        := src/main.c \
			   src/exec/exec.c \
			   src/exec/check_cmd_type.c \
 			   src/libft_utils/libft_utils.c \
 			   src/libft_utils/libft_utils2.c \
 			   src/libft_utils/libft_utils3.c \
			   src/general_utils/general_utils.c \
			   src/general_utils/ft_split.c \
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
