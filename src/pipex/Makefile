NAME := pipex 

CC := cc 

CFLAGS := -Wall -Wextra -Werror

RM := rm -rf

LIB_DIR:= lib/libft

SRCS := pipex.c utils.c command_ops.c fd_ops.c fork_ops.c parsing_utils.c pipex_utils.c error_ops.c

C_FILES := $(addprefix src/, $(SRCS))

INCLUDE := -I$(LIB_DIR) -I./include/

WITH_LIBFT := -L$(LIB_DIR) -lft

OBJS := $(C_FILES:.c=.o)

all: libft $(NAME)

$(NAME): $(OBJS)
	$(CC) $^ $(INCLUDE) $(WITH_LIBFT) -o $@

libft:
	$(MAKE) -C $(LIB_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $< $(INCLUDE) -c -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	make fclean -C $(LIB_DIR)
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re libft
