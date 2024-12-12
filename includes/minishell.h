/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:16:02 by gozon             #+#    #+#             */
/*   Updated: 2024/12/12 13:23:19 by gozon            ###   ########.fr       */
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
# include <fcntl.h>

# define ENV_SIZE 3

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
	char			**env;
	int				env_size;
	char			**path;
	int				(*builtin[8])(struct s_command *command, t_data *data);
	struct s_token	*lexer_list;
	int				exit_code;
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
	int					(*builtin)(struct s_command *command, t_data *data);
	t_redir				*redirs;
	int					pipe[2];
	pid_t				pid;
	int					errornb;
	struct s_command	*next;
}	t_command;

// Lexer

void		update_token_type(t_token *token, char *input);
int			find_closing_quote(char *input, int start, char quote_type);
void		update_word_literal(t_token *token, char *input);
void		update_str_literal(t_token *token, char *input);
int			is_separator(char c);

// Builtins

int			find_out_fd(t_command *command);
int			find_env_var(char *name, char **env, int strict);
int			mini_env(t_command *command, t_data *data);
char		*strjoin_three(char const *s1, char const *s2, char const *s3);
int			mini_echo(t_command *command, t_data *data);
int			mini_unset(t_command *command, t_data *data);
int			mini_export(t_command *command, t_data *data);
int			handle_var(char *var, t_data *data, int error);
int			mini_cd(t_command *command, t_data *data);
int			mini_pwd(t_command *command, t_data *data);

// Utils

t_token		*init_token(void);
void		clear_token(void *vtoken);
void		add_token_to_list(t_token **token_list, t_token *next_token);
void		clear_token_list(t_token **token_lst);
void		del_token_from_list(t_token **token_lst, t_token *token);
char		*begin_str(int cut, char *str);
char		*delim_strdup(const char *str, char delimiter);
void		clear_redir_list(t_redir *redir);
void		remove_var(char *var, t_data *data);
int			add_var(char *var, t_data *data);
t_command	*init_comand(void);
void		clear_command(t_command *command);
void		clear_command_list(t_command *command);
t_redir		*init_redir(void);
void		clear_redir_list(t_redir *redir);
void		free_char_array(char **array);
t_data		*init_data(void);
void		clear_data(t_data *data);
int			array_size(char **env);
char		**dup_env_array(char **envp, t_data *data);
void		replace_string(char **str1, char *str2);

#endif
