/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 08:04:11 by gozon             #+#    #+#             */
/*   Updated: 2024/12/13 13:00:09 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_command	*init_comand(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (perror("minishell"), NULL);
	command->av = NULL;
	command->status = 0;
	command->next = NULL;
	command->pid = -1;
	command->redirs = NULL;
	command->pipe[0] = 0;
	command->pipe[1] = 1;
	return (command);
}

void	clear_command(t_command *command)
{
	if (!command)
		return ;
	free_char_array(command->av);
	clear_redir_list(command->redirs);
	free(command);
}

void	clear_command_list(t_command *command)
{
	t_command	*tmp;

	if (!command)
		return ;
	tmp = command->next;
	while (tmp)
	{
		clear_command(command);
		command = tmp;
		tmp = tmp->next;
	}
	clear_command(command);
}
