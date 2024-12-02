/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_str_literal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:49:04 by nouillebobb       #+#    #+#             */
/*   Updated: 2024/12/02 10:34:58 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	update_str_literal(t_token *token, char *input)
{
	char	*str_literal;

	if (token->type == STRING_DOUBLE)
		str_literal = delim_strdup(&input[1], '\"');
	if (token->type == STRING_SIMPLE)
		str_literal = delim_strdup(&input[1], '\'');
	if (str_literal)
		token->literal = str_literal;
}

// int	main(void)
// {
// 	char	input[] = "'ascccb'sajcbs\"qdowhssodhwd";
// 	t_token	*token;

// 	token = init_token();
// 	if (!token)
// 		return (1);
// 	token->type = STRING_SIMPLE;
// 	update_str_literal(token, input);
// 	printf("%s\n", token->literal);
// 	clear_token(token);
// 	return (0);
// }
