
NAME        := minishell
CC          := cc
CFLAGS      := -Wall -Wextra -Werror
INCLUDES    := -I.
LIBS        := -lreadline

SRCS        := src/main.c \
			   src/exec.c \
 			   src/parsing/libft_utils.c \
			   src/parsing/general_utils.c \
			   src/parsing/ft_split.c \
			   src/parsing/syntax.c \
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
