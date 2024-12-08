/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 07:32:20 by gozon             #+#    #+#             */
/*   Updated: 2024/12/08 07:33:01 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	find_out_fd(t_command *command)
{
	t_redir	*redirs;
	int		out_fd;

	if (!command)
		return (-1);
	redirs = command->redirs;
	out_fd = command->pipe[1];
	while (redirs)
	{
		if (redirs->type == GREATER || redirs->type == GREATERGREATER)
			out_fd = redirs->fd;
		redirs = redirs->next;
	}
	return (out_fd);
}
