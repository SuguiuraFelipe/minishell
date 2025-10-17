
NAME        := minishell
CC          := cc
CFLAGS      := -Wall -Wextra -Werror
INCLUDES    := -I.
LIBS        := -lreadline

SRCS        := src/main.c \
 			   src/libft_utils.c \
			   src/ft_split.c \
			   src/utils.c \
			   src/syntax.c \
			   src/cmds_list.c \
			   src/input.c \
			   src/parse_pipeline.c

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
