/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:23:45 by nouillebobb       #+#    #+#             */
/*   Updated: 2025/01/14 11:08:14 by gozon            ###   ########.fr       */
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
