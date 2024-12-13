/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouillebobby <nouillebobby@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 01:11:51 by nouillebobb       #+#    #+#             */
/*   Updated: 2024/12/13 01:13:36 by nouillebobb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_command(t_data *data)
{
	t_token	*tmp;
	t_token	*prev;
	t_token	*next;
	
	tmp = data->lexer_list;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			prev = tmp->prev;
			next = tmp->next;
			tmp->prev->next = NULL;
			tmp->next->prev = NULL;
			tmp->prev = NULL;
			tmp->next = NULL;
			create_command(data);
			tmp->prev = prev;
			tmp->next = next;
		}
		tmp = tmp->next;
	}
}