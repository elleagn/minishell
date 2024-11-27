/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:29:41 by gozon             #+#    #+#             */
/*   Updated: 2024/11/27 10:39:28 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_words(char *str)
{
	int	i;
	int	res;
	int	in_word;

	i = 0;
	res = 0;
	in_word = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (in_word && str[i] == ' ')
			in_word = 0;
		if (!in_word && str[i] != ' ')
		{
			res += 1;
			in_word = 1;
		}
		i++;
	}
	return (res);
}

t_list	*tokenizer(char *input)
{
	int		i;
	t_list	*tokens;
	int		error;

	tokens = NULL;
	i = 0;
	error = 0;
	while (input[i])
	{
		if (is_operator(input[i]))
			error = add_operator(input, tokens, &i);
		else if (is_string(input[i]))
			error = add_string(input, tokens, &i);
		else
			error = add_word(input, tokens, &i);
		if (error)
			return (ft_lstclear(&tokens, clear_token), NULL);
	}
	return (tokens);
}
