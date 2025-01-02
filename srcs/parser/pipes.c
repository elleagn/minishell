/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouillebobby <nouillebobby@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:23:45 by nouillebobb       #+#    #+#             */
/*   Updated: 2025/01/02 15:24:10 by nouillebobb      ###   ########.fr       */
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