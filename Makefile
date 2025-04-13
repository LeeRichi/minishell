# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/06 14:27:00 by chlee2            #+#    #+#              #
#    Updated: 2025/04/13 17:16:14 by chlee2           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFTDIR = lib/libft
LIBFT = $(LIBFTDIR)/libft.a

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -L$(LIBFTDIR) -lft -lreadline
SRCS = src/main.c \
		src/parse.c \
		src/sig.c \
		src/sig_extra.c \
		src/buildins/echo.c \
		src/buildins/cd.c \
		src/buildins/cd_extra.c \
		src/buildins/pwd.c \
		src/buildins/exit.c \
		src/buildins/env.c \
		src/buildins/unset.c \
		src/buildins/export.c \
		src/lex/lex.c \
		src/utils/free.c \
		src/utils/free_extra.c \
		src/lex/lex_helper.c \
		src/pipex/command_ops.c \
		src/pipex/error_ops.c \
		src/pipex/error_ops_extra.c \
		src/pipex/fd_ops.c \
		src/pipex/fd_ops_extra.c \
		src/pipex/fd_ops_extra_extra.c \
		src/pipex/fd_ops_extra_extra_extra.c \
		src/pipex/fork_ops.c \
		src/pipex/fork_ops_extra.c \
		src/pipex/parsing_utils.c \
		src/pipex/pipex.c \
		src/pipex/pipex_utils.c \
		src/pipex/pipex_utils_extra.c \
		src/pipex/utils.c \
		src/pipex/heredoc.c \
		src/pipex/heredoc_extra.c \
		src/pipex/heredoc_extra_extra.c \
		src/utils/lvl_handler.c \
		src/utils/ft_split_join.c \
		src/execute.c \
		src/execute_extra.c \
		src/ft_getenv.c \
		src/lex/checkers.c \
		src/lex/parse_input_character.c \
		src/lex/parse_input_character_page_2.c \
		src/lex/parse_input_fragment.c \
		src/lex/massive_dollar_sign_handler.c \
		src/lex/handle_single_quote.c \
		src/lex/handle_double_quote.c \
		src/lex/handle_dollar_sign.c \
		src/structlize/structlize.c \
		src/structlize/structlize_p2.c \
		src/structlize/structlize_p3.c \
		src/buildins/export_helper.c \
		src/buildins/cwd_fail.c \
		src/lex/lex_helper_2.c \
		src/buildins/exit_helper.c \
		src/buildins/isNum_for_exit.c \
		src/structlize/loop_tokens_helper.c \
		src/structlize/loop_tokens_helper_p2.c \
		src/buildins/echo_helper.c \
		src/main_extra.c \

OBJS = $(SRCS:.c=.o)

all: LIBFT $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFTDIR) $(LDFLAGS)

LIBFT:
	@make -C $(LIBFTDIR)

clean:
	$(RM) $(OBJS)
	@make clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re LIBFT
