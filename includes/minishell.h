/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:16:02 by gozon             #+#    #+#             */
/*   Updated: 2024/12/09 11:35:48 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <libft.h>

# define ENV_SIZE 100

typedef enum e_type
{
	UNDEFINED,
	STRING,
	LESS,
	LESSLESS,
	GREATER,
	GREATERGREATER,
	PIPE,
	WORD
}	t_type;

typedef struct s_data
{
	char	**env;
	int		env_size;
	char	**path;
	t_list	*lexer_list;
	int		last_error;
}	t_data;

typedef struct s_token
{
	t_type				type;
	char				*literal;
	int					position;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

typedef struct s_redir
{
	t_type			type;
	char			*filename;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_command
{
	char				**av;
	t_redir				*redirs;
	int					pipe[2];
	pid_t				pid;
	int					errornb;
	struct s_command	*next;
}	t_command;

// Lexer

void	update_token_type(t_token *token, char *input);
int		find_closing_quote(char *input, int start, char quote_type);
void	update_word_literal(t_token *token, char *input);
void	update_str_literal(t_token *token, char *input);
int		is_separator(char c);

// Builtins

int		find_out_fd(t_command *command);
int		find_env_var(char *name, char **env);
int		mini_env(t_command *command, t_data *data);

// Utils

t_token	*init_token(void);
void	clear_token(void *vtoken);
void	add_token_to_list(t_token **token_list, t_token *next_token);
void	clear_token_list(t_token **token_lst);
void	del_token_from_list(t_token **token_lst, t_token *token);
char	*begin_str(int cut, char *str);
char	*delim_strdup(const char *str, char delimiter);
void	clear_redir_list(t_redir *redir);
void	remove_var(char *var, t_data *data);
int		add_var(char *var, t_data *data);

#endif
