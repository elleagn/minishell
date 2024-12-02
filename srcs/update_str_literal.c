/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_str_literal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:49:04 by nouillebobb       #+#    #+#             */
/*   Updated: 2024/12/02 10:01:48 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	update_str_literal(t_token *token, char *input)
{
	char	*str_literal;
	int		len;

	if (token->type == STRING_DOUBLE)
		str_literal = delim_strdup(&input[1], '\"');
	if (token->type == STRING_DOUBLE)
		str_literal = delim_strdup(&input[1], '\'');
	if (str_literal)
		token->literal = str_literal;
}
