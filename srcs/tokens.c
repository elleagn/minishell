/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:23:26 by gozon             #+#    #+#             */
/*   Updated: 2024/11/28 08:30:23 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*init_token(void)
{
	t_token	*token;

	token = malloc(sizeof(token));
	if (!token)
		return (NULL);
	token->literal = NULL;
	token->type = UNDEFINED;
	token->position = -1;
	return (token);
}

void	clear_token(void *vtoken)
{
	t_token	*token;

	token = (t_token *)vtoken;
	free(token->literal);
	free(token);
}
