/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouillebobby <nouillebobby@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 01:16:17 by nouillebobb       #+#    #+#             */
/*   Updated: 2024/12/13 01:18:05 by nouillebobb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_echo(t_data *data, t_token *token)
{
	t_token	*tmp;
	t_token	*prev;
	t_token	*next;
	t_token	*echo;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == ECHO)
		{
			prev = tmp->prev;
			next = tmp->next;
			tmp->prev->next = NULL;
			tmp->next->prev = NULL;
			tmp->prev = NULL;
			tmp->next = NULL;
			echo = tmp->next;
			while (echo && echo->type != ECHO)
				echo = echo->next;
			if (echo)
				echo->prev = NULL;
			parse_echo(data, tmp);
			tmp->prev = prev;
			tmp->next = next;
		}
		tmp = tmp->next;
	}
}
