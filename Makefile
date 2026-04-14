# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Zabal42                                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/28                                #+#    #+#              #
#    Updated: 2025/05/30 11:16:18 by mzabal-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -------------------------------------------------------------------- #
#                               CONFIG                                 #
# -------------------------------------------------------------------- #

NAME = minishell
TOTAL_SRC := $(words $(SRCS))
COUNT_SRC := 0
MAKEFLAGS += --no-print-directory
CC = cc

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# -------------------------------------------------------------------- #
#                     DETECCIÓN DE PLATAFORMA                          #
# -------------------------------------------------------------------- #

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    ARCH := $(shell uname -m)
    ifeq ($(ARCH),arm64)
        RL_INCLUDE = -I/opt/homebrew/opt/readline/include
        RL_LIB    = -L/opt/homebrew/opt/readline/lib
    else
        RL_INCLUDE = -I/usr/local/opt/readline/include
        RL_LIB    = -L/usr/local/opt/readline/lib
    endif
else
    RL_INCLUDE =
    RL_LIB    =
endif

CFLAGS   = -Wall -Wextra -Werror -g -I$(LIBFT_DIR)/inc $(RL_INCLUDE)
RL_FLAGS = $(RL_LIB) -lreadline

SRCS = \
	builtins/builtin_cd.c builtins/builtin_echo.c builtins/builtin_env.c \
	builtins/builtin_exit.c builtins/builtin_export.c builtins/builtin_pwd.c \
	builtins/builtin_unset.c builtins/builtin_utils.c builtins/path.c \
	executor/execute_command.c executor/exec_builtin.c executor/execute_pipeline.c \
	executor/redirections.c executor/heredoc.c executor/signals.c \
	main.c free.c tokenizer.c debug.c utils_parser.c quoted.c \
	debug_cmds.c free_cmds.c parser.c expander.c parser_tokens.c validator.c \
	utils_main.c token_classify.c token_operator.c init_cmd.c

OBJS = $(SRCS:.c=.o)

# -------------------------------------------------------------------- #
#                               COLORS                                 #
# -------------------------------------------------------------------- #

GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[1;33m
BLUE = \033[0;34m
RESET = \033[0m

# -------------------------------------------------------------------- #
#                             REGLAS                                   #
# -------------------------------------------------------------------- #

all: header $(LIBFT) $(NAME)

header:
	@echo "$(GREEN)"
	@echo "███╗   ███╗██╗███╗   ██╗██╗██╗  ██╗███████╗██╗     ██╗     "
	@echo "████╗ ████║██║████╗  ██║██║██║  ██║██╔════╝██║     ██║     "
	@echo "██╔████╔██║██║██╔██╗ ██║██║███████║█████╗  ██║     ██║     "
	@echo "██║╚██╔╝██║██║██║╚██╗██║██║██╔══██║██╔══╝  ██║     ██║     "
	@echo "██║ ╚═╝ ██║██║██║ ╚████║██║██║  ██║███████╗███████╗███████╗"
	@echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
	@echo "                 M I N I S H E L L                         "
	@echo "$(RESET)"

$(LIBFT):
	@echo "$(YELLOW)[•] Compilando libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(NAME): $(OBJS)
	@echo "$(GREEN)[•] Compilando MINISHELL...$(RESET)"
	@printf "$(GREEN)[MINISHELL]:\t$(RESET)"
	@printf "$(RED)["
	@i=0; total=$(words $(SRCS)); \
	while [ $$i -lt $$total ]; do \
		printf "$(GREEN)=$(RESET)"; \
		i=$$((i+1)); \
	done; \
	printf "$(RED)]$(RESET) $(GREEN)=> 100%%$(RESET)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(RL_FLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(BLUE)[🧹] Objetos eliminados.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(BLUE)[🧹] Limpieza total completada.$(RESET)"

re: fclean all

.PHONY: all clean fclean re header
