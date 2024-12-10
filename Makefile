# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gozon <gozon@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/27 13:33:00 by gozon             #+#    #+#              #
#    Updated: 2024/12/10 09:13:28 by gozon            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = srcs
LIBFT = libft/libft.a
SRC_FILES =	lexer/lexer.c \
			lexer/lexer_utils.c \
			lexer/update_str_literal.c \
			lexer/update_token_type.c \
			lexer/update_word_literal.c \
			utils/commands.c \
			utils/tokens.c \
			utils/redirs.c \
			builtins/builtin_utils.c \
			builtins/echo.c \
			tests/main_echo.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ_DIR = objects
SRC_DIR = srcs
OBJ = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

# Symboles Unicode
CHECK_MARK = ✔

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(OBJ) -Llibft -lft -lreadline -o $(NAME)
	@echo "$(NAME) a été créé avec succès ($(CHECK_MARK))"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(OBJ_DIR)
	@$(CC) $(CFLAGS) -Iincludes -Ilibft -c $< -o $@

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
	@mkdir $(OBJ_DIR)/lexer
	@mkdir $(OBJ_DIR)/utils
	@mkdir $(OBJ_DIR)/tests
	@mkdir $(OBJ_DIR)/builtins

$(LIBFT):
	@make -C libft --silent --no-print-directory
	@echo "Compilation de la Libft ($(CHECK_MARK))"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Nettoyage réussi ($(CHECK_MARK))"

fclean:
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	@echo "Nettoyage complet réussi ($(CHECK_MARK))"

re: fclean all

.PHONY: all clean fclean re
