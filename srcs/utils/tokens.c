/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:23:26 by gozon             #+#    #+#             */
/*   Updated: 2024/12/19 11:31:55 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*init_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (perror("minishell"), NULL);
	token->literal = NULL;
	token->type = UNDEFINED;
	token->position = -1;
	token->backup = NULL;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	clear_token(void *vtoken)
{
	t_token	*token;

	token = (t_token *)vtoken;
	if (!token)
		return ;
	free(token->literal);
	free(token->backup);
	free(token);
}

void	clear_token_list(t_token **token_lst)
{
	t_token	*token;

	if (!token_lst || !*token_lst)
		return ;
	token = *token_lst;
	while (token->prev)
		token = token->prev;
	while (token->next)
	{
		token = token->next;
		clear_token(token->prev);
	}
	clear_token(token);
	*token_lst = NULL;
}

void	add_token_to_list(t_token **token_lst, t_token *new_token)
{
	t_token	*token;

	if (!new_token || !token_lst)
		return ;
	token = *token_lst;
	if (!token)
		*token_lst = new_token;
	else
	{
		while (token->next)
			token = token->next;
		token->next = new_token;
		new_token->prev = token;
	}
}

// a tester avec le parser
void	del_token_from_list(t_token **token_lst, t_token *token)
{
	if (!token)
		return ;
	if (!token->next && !token->prev)
		*token_lst = NULL;
	else
	{
		if (token->next)
			token->next->prev = token->prev;
		if (token->prev)
			token->prev->next = token->next;
		else
			*token_lst = token->next;
	}
	clear_token(token);
}
