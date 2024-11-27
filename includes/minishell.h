/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:16:02 by gozon             #+#    #+#             */
/*   Updated: 2024/11/27 10:23:59 by gozon            ###   ########.fr       */
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

#endif
