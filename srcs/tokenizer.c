/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:29:41 by gozon             #+#    #+#             */
/*   Updated: 2024/11/26 15:37:17 by gozon            ###   ########.fr       */
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
