/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:29:41 by gozon             #+#    #+#             */
/*   Updated: 2024/12/04 09:43:30 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_unclosed_quotes(char *input)
{
	int		i;
	int		closing_quote;
	char	quote_type;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote_type = input[i];
			closing_quote = find_closing_quote(input, i, quote_type);
			if (closing_quote > 0)
				i = closing_quote;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

t_token	*create_next_token(char *input)
{
	t_token	*token;

	token = init_token();
	if (!token)
		return (NULL);
	update_token_type(token, input);
	if (token->type == STRING)
	{
		update_str_literal(token, input);
		if (!token->literal)
			return (clear_token(token), NULL);
	}
	else if (token->type == WORD)
	{
		update_word_literal(token, input);
		if (!token->literal)
			return (clear_token(token), NULL);
	}
	return (token);
}

// t_list	*lexer(char *input)
// {
// 	int		i;
// 	t_list	*token_list;
// 	t_token	*token;

// 	if (check_unclosed_quotes(input))
// 		return (NULL);
// 	token_list = NULL;
// 	i = 0;
// 	while (input[i])
// 	{
// 		token = create_next_token(&input[i]);
// 		if (!token)
// 			return (ft_lstclear(&token_list, clear_token), NULL);
// 		if (add_token_to_list(&token_list, token))
// 			return (ft_lstclear(&token_list, clear_token), clear_token(token),
// 				NULL);
// 		go_to_next_word(input, &i, token);
// 	}
// 	return (token_list);
// }
