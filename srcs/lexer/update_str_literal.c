/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_str_literal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:49:04 by nouillebobb       #+#    #+#             */
/*   Updated: 2024/12/04 09:40:45 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	find_string_end(char *input)
{
	int	i;
	int	closing_quote;

	i = 0;
	while (input[i] && !is_separator(input[i]))
	{
		if (input[i] == '\'')
		{
			closing_quote = find_closing_quote(input, i, '\'');
			if (closing_quote > 0)
				i += closing_quote;
		}
		i++;
	}
	return (i);
}

void	update_str_literal(t_token *token, char *input)
{
	char	*str_literal;
	int		cut;

	cut = find_string_end(input);
	str_literal = begin_str(cut, input);
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
