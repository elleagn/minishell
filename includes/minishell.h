/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:16:02 by gozon             #+#    #+#             */
/*   Updated: 2024/12/04 14:40:32 by gozon            ###   ########.fr       */
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
	char	**path;
	char	*pwd;
	t_list	*lexer_list;
}	t_data;

typedef struct s_token
{
	t_type		type;
	char		*literal;
	int			position;
}	t_token;

typedef struct s_redir
{
	t_type	type;
	char	*filename;
	int		fd;
	t_redir	*next;
}	t_redir;

typedef struct s_command
{
	char				**av;
	t_redir				*redirs;
	char				**heredocs;
	int					pipe[2];
	pid_t				pid;
	int					errornb;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

t_token	*init_token(void);
void	clear_token(void *vtoken);
t_token	*create_next_token(char *input);
int		add_token_to_list(t_list **token_list, t_token *next_token);
void	go_to_next_word(char *input, int *i, t_token *token);
void	update_token_type(t_token *token, char *input);
int		find_closing_quote(char *input, int start, char quote_type);
char	*begin_str(int cut, char *str);
void	update_word_literal(t_token *token, char *input);
char	*delim_strdup(const char *str, char delimiter);
void	update_str_literal(t_token *token, char *input);
int		is_separator(char c);

#endif
