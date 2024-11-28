/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:29:41 by gozon             #+#    #+#             */
/*   Updated: 2024/11/28 10:58:15 by gozon            ###   ########.fr       */
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
	t_list	*token_list;
	t_token	*token;

	token_list = NULL;
	i = 0;
	while (input[i])
	{
		token = create_next_token(&input[i]);
		if (!token)
			return (ft_lstclear(&token_list, clear_token), NULL);
		if (add_token_to_list(&token_list, token))
			return (ft_lstclear(&token_list, clear_token), clear_token(token),
				NULL);
		go_to_next_word(input, &i, token->type);
	}
	return (token_list);
}
