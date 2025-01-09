/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:59:20 by lcluzan           #+#    #+#             */
/*   Updated: 2025/01/09 12:59:21 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_pipe(t_command **current)
{
	(*current)->next = init_command();
	if (!(*current)->next)
		return (0);
	(*current)->next->previous = *current;
	*current = (*current)->next;
	return (1);
}