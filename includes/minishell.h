/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:16:02 by gozon             #+#    #+#             */
/*   Updated: 2025/01/07 14:28:25 by gozon            ###   ########.fr       */
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
# include <sys/wait.h>
# include <stdlib.h>
# include <libft.h>
# include <fcntl.h>

# define ENV_SIZE 3
# define CRITICAL_ERROR -1

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

typedef struct s_token
{
	t_type				type;
	char				*literal;
	char				*backup;
	int					position;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

typedef struct s_redir
{
	t_type			type;
	char			*filename;
	char			*backup;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_command
{
	char				**av;
	t_redir				*redirs;
	int					pipe[2];
	pid_t				pid;
	int					builtin;
	int					exit_code;
	struct s_command	*next;
	struct s_command	*previous;
}	t_command;

typedef struct s_data
{
	char			**env;
	int				env_size;
	char			**path;
	int				(*builtin[7])(struct s_command *command,
			struct s_data *data);
	struct s_token	*lexer_list;
	int				exit_code;
}	t_data;

// Loop

int			mini_loop(t_data *data);

// Lexer

void		update_token_type(t_token *token, char *input);
int			find_closing_quote(char *input, int start, char quote_type);
void		update_word_literal(t_token *token, char *input);
void		update_str_literal(t_token *token, char *input);
int			is_separator(char c);
t_token		*lexer(char *input);

// Executor

int			setup_files(t_command *command_list);
void		command_lookup(t_command *command, t_data *data);
void		close_cmd_files(t_command *command);
void		close_all_files(t_command *command_list);
void		execute_command(t_command *command, t_data *data);
void		wait_for_children(t_command *cmd, t_data *data);
void		executor(t_command *cmdlist, t_data *data);
void		wait_and_exit(t_command *cmdlist, t_data *data);
void		handle_last_command(t_command *command, t_data *data);
int			open_file(t_type type, char *filename);

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
int			mini_exit(t_command *command, t_data *data);

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
t_command	*init_command(void);
void		clear_command(t_command *command);
void		clear_command_list(t_command *command);
t_redir		*init_redir(void);
void		clear_redir(t_redir *redir);
void		clear_redir_list(t_redir *redir);
void		free_char_array(char **array);
t_data		*init_data(void);
void		clear_data(t_data *data);
int			array_size(char **env);
char		**dup_env_array(char **envp, t_data *data);
void		replace_string(char **str1, char *str2);
void		full_cleanup(t_command *command, t_data *data);
void		critical_exit(t_command *command, t_data *data);

// Parser

t_command	*parser(t_token *tokens);
int			handle_redirection(t_command *current, t_token **token);
int			handle_pipe(t_command **current);
void		add_arg(t_command *cmd, char *arg);

// Expander

int			expander(t_command *command, t_data *data);

// Tests

void    print_command(t_command *command);

#endif
