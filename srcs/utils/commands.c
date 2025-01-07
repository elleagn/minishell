/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 08:04:11 by gozon             #+#    #+#             */
/*   Updated: 2025/01/07 13:13:06 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_command	*init_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (perror("minishell"), NULL);
	command->av = NULL;
	command->next = NULL;
	command->previous = NULL;
	command->pid = -1;
	command->builtin = -1;
	command->redirs = NULL;
	command->pipe[0] = 0;
	command->pipe[1] = 1;
	command->exit_code = 0;
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
	while (command->previous)
		command = command->previous;
	tmp = command->next;
	while (tmp)
	{
		clear_command(command);
		command = tmp;
		tmp = tmp->next;
	}
	clear_command(command);
}
