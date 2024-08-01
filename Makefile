# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pchennia <pchennia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 05:22:23 by olmohame          #+#    #+#              #
#    Updated: 2024/07/31 10:54:09 by pchennia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell

CFLAGS		:= -Wextra -Wall -Werror

HEADER_READ	:= ~/.brew/opt/readline/include

LINK_READ	:= -lreadline -L ~/.brew/opt/readline/lib

HEADER_LIB	:= ./lib

HEADER_MINI := ./include

LIBFT_DIR	:= ./lib/libft

LIBFT		:= $(LIBFT_DIR)/libft.a

LINK_FT		:= -L $(LIBFT_DIR) -lft

HEADERS		:= -I$(LIBFT_DIR) -I$(HEADER_MINI) -I$(HEADER_READ) -I$(HEADER_LIB)

LIBS		:=  ${LINK_FT} ${LINK_READ}

SRCS		:=	./src/minishell.c \
				./src/parse_utills.c \
				./src/list_manipulation.c \
				./src/subs.c \
				./src/build_table.c \
				./src/red_name_expansion.c \
				./src/redirection_parser.c \
				./src/utils.c \
				./src/expansion_utils.c \
				./src/expansion_utils_2.c \
				./src/cmd_utils.c \
				./src/here_doc_handler.c \
				./src/files_utls.c \
				./src/resourse_management.c \
				./src/mem_management.c \
				./src/files_handler.c \
				./src/parse_env_var.c \
				./src/prep_pipe.c \
				./src/find_cmd_path.c \
				./src/exec_utils.c \
				./src/execute_pipeline.c \
				./src/signal/signal_handle.c \
				./src/signal/signal_utils.c \
				./src/env/convert_token.c \
				./src/env/convert_token_utils.c \
				./src/env/env.c \
				./src/env/env_utils.c \
				./src/env/utils.c \
				./src/env/update_env.c \
				./src/builtins/exec_builtin.c \
				./src/builtins/exec_cd.c \
				./src/builtins/cd_utils.c \
				./src/builtins/utils.c \
				./src/builtins/exec_pwd.c \
				./src/builtins/exec_echo.c \
				./src/builtins/exec_env.c \
				./src/builtins/exec_exit.c \
				./src/builtins/exec_export.c \
				./src/builtins/bi_exec.c \
				./src/builtins/exec_export_utils.c \
				./src/builtins/exec_unset.c \
				./src/shlvl/shlvl.c

B_SRCS		:=	./bon/minishell_bonus.c

OBJS		:= ${SRCS:.c=.o}

B_OBJS		:= ${B_SRCS:.c=.o}

BONUS		:= .bonus

CC    = cc

all: $(NAME)

$(LIBFT): FORCE
	$(MAKE) -C $(LIBFT_DIR)

FORCE:

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME):  $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) 

bonus: ${BONUS}

${BONUS}: $(LIBFT) ${B_OBJS}
	@$(CC) $(CFLAGS) $(B_OBJS) $(LIBS) $(HEADERS) -o $(NAME) 
	@touch ${BONUS}

clean:
	@rm -rf $(OBJS)
	@rm -rf $(B_OBJS)
	@cd $(LIBFT_DIR) && $(MAKE) clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf ${BONUS}
	@cd $(LIBFT_DIR) && $(MAKE) fclean

re: fclean all

norm:
	norminette $(SRCS) $(B_SRCS)

.PHONY: all clean fclean re bonus