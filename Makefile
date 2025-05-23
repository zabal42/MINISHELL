# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
<<<<<<< HEAD
#    By: mikelzabal <mikelzabal@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/12 11:24:41 by mzabal-m          #+#    #+#              #
#    Updated: 2025/05/23 09:54:58 by mikelzabal       ###   ########.fr        #
=======
#    By: jesssanc <jesssanc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/12 11:24:41 by mzabal-m          #+#    #+#              #
#    Updated: 2025/05/20 10:56:21 by jesssanc         ###   ########.fr        #
>>>>>>> jessi
#                                                                              #
# **************************************************************************** #


<<<<<<< HEAD
# Archivos fuente del parser
SRCS = main.c tokenizer.c free.c debug.c utils_parser.c quoted.c debug_cmds.c free_cmds.c parser.c expander.c parser_tokens.c
=======
NAME = minishell


SRCS =	builtins/builtin_cd.c		\
		builtins/builtin_echo.c		\
		builtins/builtin_env.c		\
		builtins/builtin_exit.c		\
		builtins/builtin_export.c	\
		builtins/builtin_pwd.c		\
		builtins/builtin_unset.c	\
		builtins/builtin_utils.c	\
		builtins/path.c				\
		executor/execute_command.c	\
		executor/exec_builtin.c		\
		executor/execute_pipeline.c	\
		executor/redirections.c		\
		executor/heredoc.c		\
		main_jess.c
>>>>>>> jessi

# Objetos
OBJS = $(SRCS:.c=.o)

# Librería libft
LIBFT_DIR = libft
LIBFT_INC = $(LIBFT_DIR)/inc
LIBFT = $(LIBFT_DIR)/libft.a

# Compilador y flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_INC)
RL_FLAGS = -lreadline

# Regla principal
all: $(LIBFT) $(NAME)

# Compilar la libft si no existe
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Compilar el ejecutable principal
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(RL_FLAGS)

# Limpiar objetos locales y de libft
clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

# Limpiar todo
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Recompilar desde cero
re: fclean all
