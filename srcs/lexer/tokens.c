/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:23:26 by gozon             #+#    #+#             */
/*   Updated: 2024/12/04 14:48:14 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*init_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->literal = NULL;
	token->type = UNDEFINED;
	token->position = -1;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	clear_token(void *vtoken)
{
	t_token	*token;

	token = (t_token *)vtoken;
	free(token->literal);
	free(token);
}

// int	main(void)
// {
// 	t_token	*token;

// 	token = init_token();
// 	if (!token)
// 		return (1);
// 	if (token->type == UNDEFINED)
// 		printf("Type : OK\n");
// 	if (token->literal == NULL)
// 		printf("Literal : OK\n");
// 	if (token->position == -1)
// 		printf("Postion : OK\n");
// 	token->literal = malloc(sizeof(char));
// 	clear_token(token);
// 	return (0);
// }
