# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gozon <gozon@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/27 13:33:00 by gozon             #+#    #+#              #
#    Updated: 2024/12/18 12:50:15 by gozon            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
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
			utils/data.c \
			utils/arrays.c \
			utils/cleanup.c \
			builtins/builtin_utils.c \
			builtins/echo.c \
			builtins/env.c \
			builtins/export_unset.c \
			builtins/export_utils.c \
			builtins/pwd_cd.c \
			builtins/add_remove_var.c \
			builtins/exit.c \
			executor/executor.c \
			executor/command_lookup.c \
			executor/files.c \
			executor/subshells.c \
			executor/last_command.c \
			tests/main_executor.c
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
	@mkdir $(OBJ_DIR)/executor

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
