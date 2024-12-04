/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:43:46 by lcluzan           #+#    #+#             */
/*   Updated: 2024/12/04 16:58:23 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*create_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->av = NULL;
	cmd->redirs = NULL;
	cmd->heredocs = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->pid = 0;
	cmd->errornb = 0;
	return (cmd);
}
