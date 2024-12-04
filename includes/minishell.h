/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:16:02 by gozon             #+#    #+#             */
/*   Updated: 2024/12/04 09:48:32 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
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

typedef struct s_token
{
	t_type		type;
	char		*literal;
	int			position;
}	t_token;

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
