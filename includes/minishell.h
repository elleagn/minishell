/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:16:02 by gozon             #+#    #+#             */
/*   Updated: 2024/11/28 10:53:23 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <libft.h>

typedef enum e_lexeme
{
	STRING_SIMPLE,
	STRING_DOUBLE,
	LESS,
	LESSLESS,
	GREATER,
	GREATERGREATER,
	PIPE,
	WORD
}	t_lexeme;

typedef struct s_token
{
	t_lexeme	type;
	char		*literal;
	int			position;
}	t_token;

t_token	*init_token(void);
void	clear_token(void *vtoken);
t_token	*create_next_token(char *input);
int		add_token_to_list(t_list **token_list, t_token *next_token);
void	go_to_next_word(char *input, int *i, t_lexeme type);

#endif
