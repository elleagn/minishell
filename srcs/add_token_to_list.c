/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_to_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:46:11 by gozon             #+#    #+#             */
/*   Updated: 2024/11/29 15:25:18 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	add_token_to_list(t_list **list, t_token *token)
{
	t_list	*node;
	t_token	*last_token;

	node = ft_lstnew(token);
	if (!node)
		return (1);
	if (!list)
		token->position = 0;
	else
	{
		last_token = (t_token *)ft_lstlast(*list)->content;
		token->position = last_token->position + 1;
	}
	ft_lstadd_back(list, node);
	return (0);
}

void	go_to_next_word(char *input, int *i, t_token *token)
{
	if (token->literal)
		*i += ft_strlen(token->literal);
	else if (token->type == GREATERGREATER || token->type == LESSLESS)
		*i += 2;
	else
		*i += 1;
	while (input[*i] == ' ')
		*i++;
}
