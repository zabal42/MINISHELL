# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzabal-m <mzabal-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/12 11:24:41 by mzabal-m          #+#    #+#              #
#    Updated: 2025/05/12 11:46:58 by mzabal-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nombre del ejecutable para test de parseo
NAME = parser_test

# Archivos fuente del parser
SRCS = main.c tokenizer.c free.c debug.c utils_parser.c

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
