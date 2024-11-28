/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_word_literal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:09:48 by gozon             #+#    #+#             */
/*   Updated: 2024/11/28 14:01:10 by gozon            ###   ########.fr       */
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
		else if (input[i] == '\'' || find_closing_quote(input, 1, '\'') >= 0)
			return (i);
		else if (input[i] == '\"' || find_closing_quote(input, 1, '\"') >= 0)
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
