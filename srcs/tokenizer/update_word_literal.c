/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_word_literal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:09:48 by gozon             #+#    #+#             */
/*   Updated: 2024/11/29 11:21:22 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_delimiter(char c, char *delimiters)
{
	int	i;

	i = 0;
	while (delimiters[i])
	{
		if (c == delimiters[i])
			return (1);
		i++;
	}
	return (0);
}

int	find_word_end(char *input)
{
	int	i;

	i = 1;
	while (input[i])
	{
		if (is_delimiter(input[i], "<>| "))
			return (i);
		else if (input[i] == '\'' && find_closing_quote(input, i, '\'') >= 0)
			return (i);
		else if (input[i] == '\"' && find_closing_quote(input, i, '\"') >= 0)
			return (i);
		i++;
	}
	return (i);
}

void	update_word_literal(t_token *token, char *input)
{
	char	*word;
	int		end_index;

	end_index = find_word_end(input);
	word = begin_str(end_index, input);
	if (word)
		token->literal = word;
}

// is_delimiter

// int	main(void)
// {
// 	printf("%i\n", is_delimiter('f', "abcde"));
// 	return (0);
// }

// find word end

// int main(void)
// {
// 	char	str[] = "bl'bl snxsnsn snxs";

// 	printf("%i\n", find_word_end(str));
// 	return (0);
// }

// update word literal

// int	main(void)
// {
// 	t_token	*token;
// 	char	str[] = "Bonjo\"ur jaime les pates";

// 	token = init_token();
// 	if (!token)
// 		return (1);
// 	update_word_literal(token, str);
// 	printf("%s\n", token->literal);
// 	clear_token(token);
// 	return (0);
// }
