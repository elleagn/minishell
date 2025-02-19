# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gozon <gozon@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/27 13:33:00 by gozon             #+#    #+#              #
#    Updated: 2025/01/16 15:30:17 by gozon            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -MMD -MP
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
			utils/signals.c \
			utils/getenv.c \
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
			executor/files_utils.c \
			parser/arguments.c \
			parser/parser.c \
			parser/pipes.c \
			parser/redirections.c \
			parser/here_doc.c \
			loop/loop.c \
			expander/expander.c \
			expander/words.c \
			expander/strings.c \
			expander/string_utils.c \
			main.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ_DIR = objects
OBJ = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)
DEPS = $(OBJ:.o=.d)

# Symboles Unicode
CHECK_MARK = ✔

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(OBJ) -Llibft -lft -lreadline -o $(NAME)
	@echo "$(NAME) a été créé avec succès ($(CHECK_MARK))"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -Iincludes -Ilibft -c $< -o $@

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
	@mkdir $(OBJ_DIR)/lexer
	@mkdir $(OBJ_DIR)/utils
	@mkdir $(OBJ_DIR)/tests
	@mkdir $(OBJ_DIR)/builtins
	@mkdir $(OBJ_DIR)/executor
	@mkdir $(OBJ_DIR)/expander
	@mkdir $(OBJ_DIR)/parser
	@mkdir $(OBJ_DIR)/loop

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

-include $(DEPS)
