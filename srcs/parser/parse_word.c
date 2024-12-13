/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:23:24 by lcluzan           #+#    #+#             */
/*   Updated: 2024/12/13 14:54:11 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parse_word(t_data *data)
{
	t_token	*token;

	token = data->lexer_list;
	while (token)
	{
		if (token->type == WORD)
			ft_printf("WORD: %s\n", token->literal);
		token = token->next;
	}
}
